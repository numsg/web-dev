# angular4框架学习准备

angular框架一直都比较火热，从angularjs(也就是angular1.x系列版本)到现在的angular4。

angular1把DI引入到前端框架，实现了数据的双向绑定及模块化，深深吸引笔者。

angular2框架是angular1框架的颠覆，可以说是推倒重来。主要是带来了性能的提升，启动时间加快；支持服务端渲染及webworker；支持移动端（安卓4.1，IOS7.1以 上）；可以灵活选择开发语言版本ES5/6，TypeScript，Dart。

angular4是直接跳过了angular3，相对于angular2框架调整比较小，主要是修复按gular2的一些BUG。

## 准备相关资料

angular4框架是笔者在做前端开发遇到的最难掌握的前端框架，没有之一，因此angular4学习有一定的门槛。这里笔者为一些计划学习angular4的读者推荐了一些基础资料，在学习angular4框架之前最好先要了解，

* [TypeScript](https://www.tslang.cn/docs/home.html)
* [Promise](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise)
* [Zone.js](http://www.cnblogs.com/whitewolf/p/zone-js.html)
* [Zone.js](https://blog.thoughtram.io/angular/2016/01/22/understanding-zones.html)
* [Rxjs](https://www.gitbook.com/book/buctwbzs/rxjs/details)


TypeScript：angular4框架就是基于TypeScript编写的，了解TypeScript基础语法是必须的。

Promise：angular4框架使用了大量的Promise，如果你Promise都不理解，根本不理解代码执行顺序。

Zone：Angular4框架是运行在Zone上的，主要是为里面一些异步执行提供了一些钩子。

Rxjs: Angular4框架引入Rxjs主要是为了实现响应式编程。


有了以上基础，在来撸angular框架就比较简单了。

主要分下面几个点来剖析Angular4框架：

* Angular4 DI实现原理（TODO）

* Angular4 注解实现原理(如@NgModule)（TODO）

* Angular4 变化检查实现原理（TODO）

* Angular4 启动一个Angular4应用程序前准备工作（TODO）

* Angular4 启动一个Module的流程（TODO）

* Angular4 路由机制（TODO）

* Angular4 拓展（TODO）

