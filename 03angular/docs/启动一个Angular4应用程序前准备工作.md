# 启动一个Angular4应用程序前准备工作

今天来介绍一下Angular应用程序启动前的准备工作，首先我们先看一个简单Angular应用程序的入口，代码如下

```
imort { enableProdMode } from '@angular/core';
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic';

import { AppModule } from './app/app.module';

if (process.env.ENV === 'production') {
    enableProdMode();
} else {

}

platformBrowserDynamic().bootstrapModule(AppModule);

```

这一段代码主要有四个部分组成：

1. 引用Angular相关的核心类
2. 定义了一个Module
3. 根据环境变量确认是生产环境还是调试环境
4. 调用Angular的启动函数，实现启动功能。

从上面代码片段来看，关键代码可以分为三点：

1. 判断当前的环境是否是生产环境
2. 调用platformBrowserDynamic()构造当前客户端运行的平台环境
3. 调用bootstrapModule()指定启动AppModule

今天主要介绍的是第一，第二点，下面我们来一点一点剖析。

## 判断当前的环境是否是生产环境
判断当前是生产环节还是开发环境

```
if (process.env.ENV === 'production') {
    enableProdMode();
} else {

}
```
如果是生产环境，则调用enableProdMode(),设置_devMode = false。
```
export function enableProdMode() {
    if (_runModeLocked) {
        throw new Error('Cannot enable prod mode after platform setup.');
    }
    _devMode = false;
}
```
这个设置的主要目的是在_devMode = true条件下，里面有好多的调试日志信息。

## 构造当前客户端运行的平台环境

platformBrowserDynamic方法

```
export var platformBrowserDynamic = createPlatformFactory(platformCoreDynamic, 'browserDynamic', INTERNAL_BROWSER_DYNAMIC_PLATFORM_PROVIDERS);
```

可以看出这个方法是通过调用createPlatformFactory方法得到的，生成的时候会传入三个参数，其中有第二个参数是字符串'browserDynamic'，我们看看其它两个参数都是什么。

platformCoreDynamic参数，这个参数比较有意思，它的实现也是在调用createPlatformFactory方法返回一个function，代码如下，
```
export var /** @type {?} */ platformCoreDynamic = createPlatformFactory(platformCore, 'coreDynamic', [
    { provide: COMPILER_OPTIONS, useValue: {}, multi: true },
    { provide: CompilerFactory, useClass: JitCompilerFactory },
    { provide: PLATFORM_INITIALIZER, useValue: _initReflector, multi: true },
]);
```
而platformCore它的实现也是在调用createPlatformFactory方法返回一个function，代码如下，
```
export var /** @type {?} */ platformCore = createPlatformFactory(null, 'core', _CORE_PLATFORM_PROVIDERS);
```

看得有些混乱，是吧。下面用一个简单示例来让大家更好了解里面执行顺序，
```
function execFun(funx,c){
  console.log(c);
  return function fun(z){
    if(z==undefined){
      z = 1;
    }
    if(funx){
      funx(z+c);
    }
    else{
      console.log(z+c);
    }
    return 1;
  }
};

var funA = execFun(null,11);
var funB =execFun(funA,22);
var funC =execFun(funB,33);

funC();
```
输出结果如下,
```
11
22
33
67
```
因此我们可以知道platformBrowserDynamic()里面执行顺序是
```
platformBrowserDynamic //3. 最后执行platformBrowserDynamic返回内部方法
     |
     +---> platformCoreDynamic //2. 再执行platformCoreDynamic返回内部方法
                |
                +---> platformCore //1. 首先platformCore返回的内部方法，

```
下面我们再来分析createPlatformFactory方法就简单了
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

可以看出在createPlatformFactory方法中，只是简单的返回了一个内部方法。当我们调用platformBrowserDynamic()时，实际就是调用这个内部方法。

大致总结如下，
1. 由于它传入的parentPlatformFactory是null，因此首先调用createPlatform创建平台环境并返回PlatformRef，并且还初始化好了IOC容器ReflectiveInjector。
2. 后面执行的platformCoreDynamic和platformBrowserDynamic的parentPlatformFactory都不是null，所以它也没干别的事情，就是为了触发内部方法，另外在触发的同时它将所有provider进行了合并。

步骤1中createPlatform，创建平台，
```
export function createPlatform(injector: Injector): PlatformRef {
  if (_platform && !_platform.destroyed) {
    throw new Error(
        'There can be only one platform. Destroy the previous one to create a new one.');
  }
  _platform = injector.get(PlatformRef);
  const inits: Function[] = <Function[]>injector.get(PLATFORM_INITIALIZER, null);
  if (inits) inits.forEach(init => init());
  return _platform;
}
```
在这段代码使用到了[Injector](https://github.com/numsg/web-dev/blob/master/03angular/docs/Angular4%20DI%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.md)的特性来创建的。创建完以后会获取所有名为PLATFORM_INITIALIZER的Provider，然后调用它。

至此platformBrowserDynamic()执行过程已经全部理清楚了，在这个过程中会创建Injector和platform，其中[Injector](https://github.com/numsg/web-dev/blob/master/03angular/docs/Angular4%20DI%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.md)是依赖注入的关键。
在分析的过程中，发现可以通过定义一个PLATFORM_INITIALIZER名称的Provider实现在初始化Platform后执行代码。示例代码：
```
function test(){
   console.log("This is a test!");
}

platformBrowserDynamic([{provide: PLATFORM_INITIALIZER, useValue: test, multi: true}]).bootstrapModule(AppModule);
```





