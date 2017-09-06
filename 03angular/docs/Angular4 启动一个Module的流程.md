# Angular4 启动一个Module的流程

前面我们分析了Angular4在bootStrap前做的事情，主要是准备Angular4框架运行的平台。其中platformBrowserDynamic()最后返回的是PlatformRef。bootstrapModule是PlatformRef_的一个方法，
```
PlatformRef_.prototype.bootstrapModule = function (moduleType, compilerOptions) {
        if (compilerOptions === void 0) { compilerOptions = []; }
        return this._bootstrapModuleWithZone(moduleType, compilerOptions, null);
    };
```
这个方法中实现了Module的初始化、Component的初始化等，是Angular框架的启动函数。

Angular是运行在Zone上的，Zone可以理解为一个第三方库，而Angular又对Zone做了一层封装，叫ng_zone(为什么引入Zone，可以见到理解为Angular希望对一些异步的操作方法进行管理控制)，这里就不展开分析Zone了。

下面我们看一下_bootstrapModuleWithZone这个方法做了什么。
```
 PlatformRef_.prototype._bootstrapModuleWithZone = function (moduleType, compilerOptions, ngZone, componentFactoryCallback) {
        var _this = this;
        if (compilerOptions === void 0) { compilerOptions = []; }
        var /** @type {?} */ compilerFactory = this.injector.get(CompilerFactory);
        var /** @type {?} */ compiler = compilerFactory.createCompiler(Array.isArray(compilerOptions) ? compilerOptions : [compilerOptions]);
        // ugly internal api hack: generate host component factories for all declared components and
        // pass the factories into the callback - this is used by UpdateAdapter to get hold of all
        // factories.
        if (componentFactoryCallback) {
            return compiler.compileModuleAndAllComponentsAsync(moduleType)
                .then(function (_a) {
                var ngModuleFactory = _a.ngModuleFactory, componentFactories = _a.componentFactories;
                componentFactoryCallback(componentFactories);
                return _this._bootstrapModuleFactoryWithZone(ngModuleFactory, ngZone);
            });
        }
        return compiler.compileModuleAsync(moduleType)
            .then(function (moduleFactory) { return _this._bootstrapModuleFactoryWithZone(moduleFactory, ngZone); });
    };
```
1. 通过Injector得到一个Compiler的Factory(有人会问，这个CompilerFactory为什么已经在Angular的DI容器中)，这个要回到准备Angular启动平台，在创建platformCoreDynamic时就已经把CompilerFactory注入到Angular DI容器中了
```
export var /** @type {?} */ platformCoreDynamic = createPlatformFactory(platformCore, 'coreDynamic', [
    { provide: COMPILER_OPTIONS, useValue: {}, multi: true },
    { provide: CompilerFactory, useClass: JitCompilerFactory },
    { provide: PLATFORM_INITIALIZER, useValue: _initReflector, multi: true },
]);
```
2. 然后通过compilerFactory和option创建一个compiler用于Module和Component的编译。

3. compileModuleAsync，异步编译module，编译成功后会返回一个moduleFactory，再调用_bootstrapModuleFactoryWithZone来启动module。


下面我们先分析下createCompiler，
```
JitCompilerFactory.prototype.createCompiler = function (options) {
        if (options === void 0) { options = []; }
        var /** @type {?} */ mergedOptions = _mergeOptions(this._defaultOptions.concat(options));
        var /** @type {?} */ injector = ReflectiveInjector.resolveAndCreate([
            COMPILER_PROVIDERS, {
                provide: CompilerConfig,
                useFactory: function () {
                    return new CompilerConfig({
                        // let explicit values from the compiler options overwrite options
                        // from the app providers. E.g. important for the testing platform.
                        genDebugInfo: mergedOptions.useDebug,
                        // let explicit values from the compiler options overwrite options
                        // from the app providers
                        useJit: mergedOptions.useJit,
                        // let explicit values from the compiler options overwrite options
                        // from the app providers
                        defaultEncapsulation: mergedOptions.defaultEncapsulation,
                        logBindingUpdate: mergedOptions.useDebug
                    });
                },
                deps: []
            },
            mergedOptions.providers
        ]);
        return injector.get(Compiler);
    };
```
首先合并编译配置，接着创建一个DI容器，注入一些COMPILER_PROVIDERS/CompilerConfig，返回一个Compiler实例，就是JitCompiler
```
 { provide: Compiler, useExisting: JitCompiler },
```

再分析compileModuleAsync，compileModuleAsync是JitCompiler的一个方法，
```
 JitCompiler.prototype.compileModuleAsync = function (moduleType) {
        return this._compileModuleAndComponents(moduleType, false).asyncResult;
    };
```
compileModuleAsync深层次的调用顺序依次是
```
compileModuleAsync
         |
         +--->_compileModuleAndComponents
                       |
                       +--->_loadModules,_compileComponents,_compileModule

```

_loadModules,加载Module的时候，首先是通过getNgModuleMetadata方法获取Model的meta数据（meta数据其实就是我们定义Module的注解信息），在这个方法中
会得到class通过NgModule注解修饰的信息。

```
if (meta.imports){
   ......
}
if (meta.exports){
   ......
}
if (meta.declarations){
   ......
}
if (meta.providers){
   ......
}
if (meta.entryComponents){
   ......
}
if (meta.bootstrap){
   ......
}
if (meta.schemas){
   ......
}
```
每一个判断语句内都是对各种信息的处理，最后把得到的信息组合成一个CompilerMeta。其中需要特别注意的是transitiveModule属性
这个属性记录了Module内使用到的各种信息，包括Module，Component，Provider，Pipe，Directive。
在获取了Module的Compiler信息后就需要进行加载了

```
CompileMetadataResolver.prototype.loadNgModuleDirectiveAndPipeMetadata = function (moduleType, isSync, throwIfNotFound) {
        var _this = this;
        if (throwIfNotFound === void 0) { throwIfNotFound = true; }
        var /** @type {?} */ ngModule = this.getNgModuleMetadata(moduleType, throwIfNotFound);
        var /** @type {?} */ loading = [];
        if (ngModule) {
            ngModule.declaredDirectives.forEach(function (id) {
                var /** @type {?} */ promise = _this._loadDirectiveMetadata(id.reference, isSync);
                if (promise) {
                    loading.push(promise);
                }
            });
            ngModule.declaredPipes.forEach(function (id) { return _this._loadPipeMetadata(id.reference); });
        }
        return Promise.all(loading);
    };
```

通过代码可以看出：
1. 加载通过declared声明的directive（包括Component）
2. 加载pipe

这两步都是对使用到的类的元数据进行处理。

上面是加载module，再看_compileComponents

加载完Module的全部信息后就要对Module中的Component进行编译，编译过程：
1、收集Module中的全部Component
2、收集每一个Component中使用到的entryComponents
3、收集Module中使用到的entryComponents
4、使用收集到的信息进行编译

```
JitCompiler.prototype._compileDirectiveWrapper = function (dirMeta, moduleMeta) {
    var /** @type {?} */ compileResult = this._directiveWrapperCompiler.compile(dirMeta);
    var /** @type {?} */ statements = compileResult.statements;
    var /** @type {?} */ directiveWrapperClass;
    if (!this._compilerConfig.useJit) {
        directiveWrapperClass = interpretStatements(statements, compileResult.dirWrapperClassVar);
    }
    else {
        directiveWrapperClass = jitStatements("/" + identifierName(moduleMeta.type) + "/" + identifierName(dirMeta.type) + "/wrapper.ngfactory.js", statements, compileResult.dirWrapperClassVar);
    }
    this._compiledDirectiveWrapperCache.set(dirMeta.type.reference, directiveWrapperClass);
};
```
这是调用编译的入口，具体编译过程不再这里分析，两种编译方式的区别：使用jit会在客户端(浏览器)中生成具体的代码文件，可以在浏览器查看本地文件看到，不适用jit的方式则会编译保存在内存中。

最后看_compileModule，Module的编译过程和Component编译过程类似，首先进行数据收集和初始化，然后进行编译。

```
JitCompiler.prototype._compileModule = function (moduleType) {
        var _this = this;
        var /** @type {?} */ ngModuleFactory = this._compiledNgModuleCache.get(moduleType);
        if (!ngModuleFactory) {
            var /** @type {?} */ moduleMeta_1 = this._metadataResolver.getNgModuleMetadata(moduleType);
            // Always provide a bound Compiler
            var /** @type {?} */ extraProviders = [this._metadataResolver.getProviderMetadata(new ProviderMeta(Compiler, { useFactory: function () { return new ModuleBoundCompiler(_this, moduleMeta_1.type.reference); } }))];
            var /** @type {?} */ compileResult = this._ngModuleCompiler.compile(moduleMeta_1, extraProviders);
            compileResult.dependencies.forEach(function (dep) {
                dep.placeholder.reference =
                    _this._assertComponentKnown(dep.comp.reference, true).proxyComponentFactory;
            });
            if (!this._compilerConfig.useJit) {
                ngModuleFactory =
                    interpretStatements(compileResult.statements, compileResult.ngModuleFactoryVar);
            }
            else {
                ngModuleFactory = jitStatements("/" + identifierName(moduleMeta_1.type) + "/module.ngfactory.js", compileResult.statements, compileResult.ngModuleFactoryVar);
            }
            this._compiledNgModuleCache.set(moduleMeta_1.type.reference, ngModuleFactory);
        }
        return ngModuleFactory;
    };
```

也有jit和非jit两种方式，两种方式都会返回一个ModuleFactory作为最终的编译结果。

上面所有编译完成后会得到一个ModuleFactory，看下面代码
```
 var /** @type {?} */ createResult = function () {
            _this._compileComponents(moduleType, null);
            return _this._compileModule(moduleType);
        };

if (isSync) {
    return new SyncAsyncResult(createResult());
}
else {
    return new SyncAsyncResult(null, loadingPromise.then(createResult));
}

export var SyncAsyncResult = (function () {
    /**
     * @param {?} syncResult
     * @param {?=} asyncResult
     */
    function SyncAsyncResult(syncResult, asyncResult) {
        if (asyncResult === void 0) { asyncResult = null; }
        this.syncResult = syncResult;
        this.asyncResult = asyncResult;
        if (!asyncResult) {
            this.asyncResult = Promise.resolve(syncResult);
        }
    }
    return SyncAsyncResult;
}());
```
然后使用这个Factory来启动我们的程序。

```
return compiler.compileModuleAsync(moduleType)
    .then((moduleFactory) => this._bootstrapModuleFactoryWithZone(moduleFactory, ngZone));
```
这段函数的后半部分就是进行启动，其中用到的moduleFactory就是前半部分编译后得到的。
在看_bootstrapModuleFactoryWithZone代码
```
PlatformRef_.prototype._bootstrapModuleFactoryWithZone = function (moduleFactory, ngZone) {
        var _this = this;
        if (!ngZone)
            ngZone = new NgZone({ enableLongStackTrace: isDevMode() });
        return ngZone.run(function () {
            var /** @type {?} */ ngZoneInjector = ReflectiveInjector.resolveAndCreate([{ provide: NgZone, useValue: ngZone }], _this.injector);
            var /** @type {?} */ moduleRef = (moduleFactory.create(ngZoneInjector));
            var /** @type {?} */ exceptionHandler = moduleRef.injector.get(ErrorHandler, null);
            if (!exceptionHandler) {
                throw new Error('No ErrorHandler. Is platform module (BrowserModule) included?');
            }
            moduleRef.onDestroy(function () { return ListWrapper.remove(_this._modules, moduleRef); });
            ngZone.onError.subscribe({ next: function (error) { exceptionHandler.handleError(error); } });
            return _callAndReportToErrorHandler(exceptionHandler, function () {
                var /** @type {?} */ initStatus = moduleRef.injector.get(ApplicationInitStatus);
                return initStatus.donePromise.then(function () {
                    _this._moduleDoBootstrap(moduleRef);
                    return moduleRef;
                });
            });
        });
    };
```
这里主要是使用NgZone把Angular启动包装了一层，使得Angular运行在Zone之上。主要是对里面异步的控制。

来看看_moduleDoBootstrap
```
PlatformRef_.prototype._moduleDoBootstrap = function (moduleRef) {
        var /** @type {?} */ appRef = moduleRef.injector.get(ApplicationRef);
        if (moduleRef.bootstrapFactories.length > 0) {
            moduleRef.bootstrapFactories.forEach(function (compFactory) { return appRef.bootstrap(compFactory); });
        }
        else if (moduleRef.instance.ngDoBootstrap) {
            moduleRef.instance.ngDoBootstrap(appRef);
        }
        else {
            throw new Error(("The module " + stringify(moduleRef.instance.constructor) + " was bootstrapped, but it does not declare \"@NgModule.bootstrap\" components nor a \"ngDoBootstrap\" method. ") +
                "Please define one of these.");
        }
        this._modules.push(moduleRef);
    };
```
有两种方式进行bootstrap：
1. bootstrapFactories的长度大于0，使用appRef的bootstrap函数进行启动，当我们在NgModule中配置了bootstrap属性的时候，就会记录到这里来。
2. 使用moduleRef.instance的ngDoBootstrap方法进行启动，这个moduleRef.instance就是我们的NgModule修饰的类。
如果上述两种都没有的话就会报错，所以在实现作为启动Module的时候，要么注解中配置bootstrap属性，要么类中定义ngDoBootstrap方法。

appRef实际是ApplicationRef_类的实例，bootstrap的代码为：
```
ApplicationRef_.prototype.bootstrap = function (componentOrFactory) {
        var _this = this;
        if (!this._initStatus.done) {
            throw new Error('Cannot bootstrap as there are still asynchronous initializers running. Bootstrap components in the `ngDoBootstrap` method of the root module.');
        }
        var /** @type {?} */ componentFactory;
        if (componentOrFactory instanceof ComponentFactory) {
            componentFactory = componentOrFactory;
        }
        else {
            componentFactory = this._componentFactoryResolver.resolveComponentFactory(componentOrFactory);
        }
        this._rootComponentTypes.push(componentFactory.componentType);
        var /** @type {?} */ compRef = componentFactory.create(this._injector, [], componentFactory.selector);
        compRef.onDestroy(function () { _this._unloadComponent(compRef); });
        var /** @type {?} */ testability = compRef.injector.get(Testability, null);
        if (testability) {
            compRef.injector.get(TestabilityRegistry)
                .registerApplication(compRef.location.nativeElement, testability);
        }
        this._loadComponent(compRef);
        if (isDevMode()) {
            this._console.log("Angular is running in the development mode. Call enableProdMode() to enable the production mode.");
        }
        return compRef;
    };
```

在这段代码中主要干的事情有：
1. 获取Component Factory
2. 创建根Component
3. 注册测测试组件
4. 加载Component
5. 显示调试信息，在开发模式下每次启动时console中显示的那段话就是在这里打印的

加载Component的代码如下，
```
ApplicationRef_.prototype._loadComponent = function (componentRef) {
        this.attachView(componentRef.hostView);
        this.tick();
        this._rootComponents.push(componentRef);
        // Get the listeners lazily to prevent DI cycles.
        var /** @type {?} */ listeners = (this._injector.get(APP_BOOTSTRAP_LISTENER, [])
            .concat(this._bootstrapListeners));
        listeners.forEach(function (listener) { return listener(componentRef); });
    };
```

1. 把Component的vie和application进行关联
2. 只是一个tick（主要是做变化检测）
3. 添加到跟Component列表中去（可以看出Angular是支持多个跟节点的）
4. 从Injector中获取APP_BOOTSTRAP_LISTENER名称的方法，然后调用。

至此Angular的整个启动过程主线就全部分析完了








