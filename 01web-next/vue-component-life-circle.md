---
title: Vue Component Life Circle
created: '2020-04-24T09:31:12.066Z'
modified: '2020-04-27T03:05:05.709Z'
---

# Vue Component Life Circle

## 1. mounted
组件挂载到dom后执行。可以在`mounted`中调用接口获取数据、订阅事件、开启定时器、添加EventListener
```ts
mounted() {
  userService.getUsers().then((data) => {
    this.users = data;
  });

  rxevent.subscribe('Event', 'Key', () => {
    // do somethings
  });

  const timerId = setInterval(() => {
    // do somethings
  }, 1000);

  element.addEventListener('mousewheel', () => {
    // do somethings
  });
}
```


## 2. beforeDestroy
组件销毁前执行。要在该方法内取消订阅事件
```ts
beforeDestroy() {
  rxevent.unsubscribe('Event', 'Key');
}
```

如果取消订阅要依赖订阅方法的返回值，可以在`mounted`中使用`$once`来执行`beforeDestroy`
```ts
mounted() {
  const timerId = setInterval(() => {
    // do somethings
  });

  const subscription = observer.subscribe(() => {
    // do somethings
  });

  this.$once('hook:beforeDestroy', () => {
    // 清除定时器
    clearInterval(timerId);

    // 取消Observable订阅
    subscription.unsubscribe();
  });
}
```

> 如果将`mounted`和`beforeDestroy`分开写，就需要将`timerId`和`subscription`定义到组件的属性上
