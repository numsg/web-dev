# Angular4 DI实现原理

DI可一说是Angular框架的一个亮点，也是首个前端框架将DI概念引入到前端工程。可能了解C#或者Java的人对DI一点都不陌生，在这里就不详细解释DI是什么了（不知道DI的先去了解下DI这个概念是什么）。

那么Angular框架是怎样实现DI的呢。

在看Angular框架源码时，你会经常发现这样的代码

```
injector.get(key) // 获取某个对象的实例
```
在我们写Angular应用程序时，我们编写一个通用类（也可以成为Service），然后打上注解@Injectable()，然后导出成模块的Provider，示例代码如下，

```
import { NGWebSocketService } from './services/ng-websocket.service';

@NgModule({
    imports: [
        ...
    ],
    exports: [
        ...
    ],
    providers: [
        NGWebSocketService
    ]
})
```
然后再别的模块可以导入，直接使用这个Service。实际这个过程也是用到了Angular框架的DI。

好的，下面再来探索一下Angular框架DI的实现机制。

DI的核心部分无非就是为某个接口注册实现类，根据接口获取实现类的实例过程（当然里面还有生命周期等其他的一些概念，这里只介绍注册与获取）。

## 获取实例

Angular框架需要一个类的实例的时候只需要调用injector.get方法就能够得到。这个Injector就是Angular依赖注入的基础，任何可以被注入的类都是都可以通过injector.get方法来获取。

Injector是一个接口，实际实例化的类为ReflectiveInjector_。继承关系为

```
ReflectiveInjector_ -> ReflectiveInjector -> Injector
```

injector.get最后调用的方法其实就是ReflectiveInjector_.prototype.get方法。

查看ReflectiveInjector_.get方法的代码，我们可以发现其调用关系为：

```
get -> _getByKey -> _getByKeyDefault -> _getObjByKeyId
```

如果调用自己的 _getObjByKeyId没有找到实例，就会查找父Injector的 _getObjByKeyId，一直向上查找。源码如下，

```
ReflectiveInjector_.prototype._getByKeyDefault = function (key, notFoundValue, visibility) {
        var /** @type {?} */ inj;
        if (visibility instanceof SkipSelf) {
            inj = this._parent;
        }
        else {
            inj = this;
        }
        while (inj instanceof ReflectiveInjector_) {
            var /** @type {?} */ inj_ = (inj);
            var /** @type {?} */ obj = inj_._getObjByKeyId(key.id);
            if (obj !== UNDEFINED)
                return obj;
            inj = inj_._parent;
        }
        if (inj !== null) {
            return inj.get(key.token, notFoundValue);
        }
        else {
            return this._throwOrNull(key, notFoundValue);
        }
    };
```

在_getObjByKeyId如果具有声明但是没有实例化，就会去实例化并返回，具体代码如下：

```
ReflectiveInjector_.prototype._getObjByKeyId = function (keyId) {
        for (var /** @type {?} */ i = 0; i < this.keyIds.length; i++) {
            if (this.keyIds[i] === keyId) {
                if (this.objs[i] === UNDEFINED) {
                    this.objs[i] = this._new(this._providers[i]);
                }
                return this.objs[i];
            }
        }
        return UNDEFINED;
    };
```

然后调用_new()进行实例化。Angular框架做了循环依赖检查，代码如下，

```
ReflectiveInjector_.prototype._new = function (provider) {
        if (this._constructionCounter++ > this._getMaxNumberOfObjects()) {
            throw new CyclicDependencyError(this, provider.key);
        }
        return this._instantiateProvider(provider);
    };
```

_instantiateProvider 调用 _instantiate创建实例.其中 _getByReflectiveDependency方法会去查找依赖的事例，如果依赖的事例没有被创建，就会先去创建，这里就会有可能造成循环依赖。，具体代码如下，

```
ReflectiveInjector_.prototype._instantiate = function (provider, ResolvedReflectiveFactory) {
        var _this = this;
        var /** @type {?} */ factory = ResolvedReflectiveFactory.factory;
        var /** @type {?} */ deps;
        try {
            deps =
                ResolvedReflectiveFactory.dependencies.map(function (dep) { return _this._getByReflectiveDependency(dep); });
        }
        catch (e) {
            if (e instanceof AbstractProviderError || e instanceof InstantiationError) {
                e.addKey(this, provider.key);
            }
            throw e;
        }
        var /** @type {?} */ obj;
        try {
            obj = factory.apply(void 0, deps);
        }
        catch (e) {
            throw new InstantiationError(this, e, e.stack, provider.key);
        }
        return obj;
    };
```

## 注册实现

在了解注册实例前，我们先要理解Provider，在Angular框架中Provider可以理解为是Angular对于依赖注入项的一个描述，一个对象可以被依赖注入，就必须有一个Provider对其进行描述。Injector根据这个Provider才能够创建实例。

Provider分为5中类型，

| 类型        | 	说明   |
| --------   | ---------|
| TypeProvider        | 任意类型的类，任意一个类都可以成为一个Provider，Angular会对其进行包装，Factory就是new一个这个类型的事例，都是单例的  |
| ValueProvider        | 使用具体的值作为实例的 |
| ClassProvider        | 使用具体class来创建事例，和TypeProvider类似，但是可以设置为multi |
| ExistingProvider     | 使用一个已有的Provider，相当于给已有的Provider设置一个别名 |
| FactoryProvider     | 使用自己的创建工厂来实例化Provider，可以设置创建的依赖项 |

Injector在创建一个事例的时候就是使用Provider的Factory和deps来实例化（具体如上面的代码所示）。

从上面的分析我们可以发现，这么多种Provider中只有FactoryProvider是需要设置Factory和deps的，然而在Injector创建实例的时候是必须需要Factory的，那么其它类型的Provider的Factory又是怎么来的呢？
通过跟踪代码，我们可以发现如下代码：

```
function resolveReflectiveFactory(provider) {
    var /** @type {?} */ factoryFn;
    var /** @type {?} */ resolvedDeps;
    if (provider.useClass) {
        var /** @type {?} */ useClass = resolveForwardRef(provider.useClass);
        factoryFn = reflector.factory(useClass);
        resolvedDeps = _dependenciesFor(useClass);
    }
    else if (provider.useExisting) {
        factoryFn = function (aliasInstance) { return aliasInstance; };
        resolvedDeps = [ReflectiveDependency.fromKey(ReflectiveKey.get(provider.useExisting))];
    }
    else if (provider.useFactory) {
        factoryFn = provider.useFactory;
        resolvedDeps = constructDependencies(provider.useFactory, provider.deps);
    }
    else {
        factoryFn = function () { return provider.useValue; };
        resolvedDeps = _EMPTY_LIST;
    }
    return new ResolvedReflectiveFactory(factoryFn, resolvedDeps);
}
```

从这段代码可以发现，Angular从新计算了他们的Factory和deps。

好的，了解了Provider后，我们再看下，注册实现的过程，

在初始化平台过程中使用ReflectiveInjector.resolveAndCreate方法可以创建一个Injector,代码如下，

```
export function createPlatformFactory(parentPlatformFactory, name, providers) {
    if (providers === void 0) { providers = []; }
    var /** @type {?} */ marker = new OpaqueToken("Platform: " + name);
    return function (extraProviders) {
        if (extraProviders === void 0) { extraProviders = []; }
        if (!getPlatform()) {
            if (parentPlatformFactory) {
                parentPlatformFactory(providers.concat(extraProviders).concat({ provide: marker, useValue: true }));
            }
            else {
                createPlatform(ReflectiveInjector.resolveAndCreate(providers.concat(extraProviders).concat({ provide: marker, useValue: true })));
            }
        }
        return assertPlatform(marker);
    };
}
```
resolveAndCreate方法的第一个参数是我们需要使用到的Provider列表，第二个参数就是父Injector。
```
ReflectiveInjector.resolveAndCreate = function (providers, parent) {
        if (parent === void 0) { parent = null; }
        var /** @type {?} */ ResolvedReflectiveProviders = ReflectiveInjector.resolve(providers);
        return ReflectiveInjector.fromResolvedProviders(ResolvedReflectiveProviders, parent);
    };
```

下一步执行ReflectiveInjector.resolve(providers) -> resolveReflectiveProviders(providers)

```
export function resolveReflectiveProviders(providers) {
    var /** @type {?} */ normalized = _normalizeProviders(providers, []);
    var /** @type {?} */ resolved = normalized.map(resolveReflectiveProvider);
    var /** @type {?} */ resolvedProviderMap = mergeResolvedReflectiveProviders(resolved, new Map());
    return Array.from(resolvedProviderMap.values());
}
```

这方法主要做的是格式化Provider

1. 把provider列表理顺，如：[[p1,p2],p3,[p4,p5]]理顺为[p1,p2,p3,p4,p5]
2. 封装provider，就是上面添加Factory和deps的内容。
3. 合并相同的Provider，如果不支持multi的Provider声明的了多个，就会抛出异常。

这就是注册实现的整个过程。

Angular的DI原理分析就到此结束。



