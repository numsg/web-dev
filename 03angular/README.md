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


有了以上基础，在来看angular框架就比较简单了。

主要分下面几个点来剖析Angular4框架：

* [Angular4 DI实现原理](https://github.com/numsg/web-dev/blob/master/03angular/docs/Angular4%20DI%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.md)

* [Angular4 注解实现原理(如@NgModule)](https://github.com/numsg/web-dev/blob/master/03angular/docs/Angular4%20%E6%B3%A8%E8%A7%A3%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.md)

* Angular4 变化检查实现原理（TODO）

* [Angular4 启动一个Angular4应用程序前准备工作](https://github.com/numsg/web-dev/blob/master/03angular/docs/%E5%90%AF%E5%8A%A8%E4%B8%80%E4%B8%AAAngular4%E5%BA%94%E7%94%A8%E7%A8%8B%E5%BA%8F%E5%89%8D%E5%87%86%E5%A4%87%E5%B7%A5%E4%BD%9C.md)

* [Angular4 启动一个Module的流程](https://github.com/numsg/web-dev/blob/master/03angular/docs/Angular4%20%E5%90%AF%E5%8A%A8%E4%B8%80%E4%B8%AAModule%E7%9A%84%E6%B5%81%E7%A8%8B.md)

* Angular4 路由机制（TODO）

* Angular4 拓展（TODO）

