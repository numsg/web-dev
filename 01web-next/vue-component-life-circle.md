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

***

如果url中带有参数，例如`/incident/:incidentId`。还需要在路由组件的`beforeRouteUpdate`勾子中获取数据。警情id参数改变时只会触发`beforeRouteUpdate`
```ts
mounted() {
  this.getData();
}

beforeRouteUpdate(to: Route, from: Route, next: NextFn) {
  this.getData();
  next();
}


private getData() {
  const incidentId = this.$route.params.incidentId;
  axios.get<Incident>('http://xxx/' + incidentId).then((result) => {
    this.incident = result;
  });
}
```

路由组件中使用路由勾子需要注册
```ts
Component.registerHooks(['beforeRouteUpdate']);

@Component
export default class HelloWorld extends Vue {}
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

  const handleMouseWhell = () => {
    // do something
  }

  // 监听dom事件
  window.addEventListener('mousewheel', handleMouseWhell);

  this.$once('hook:beforeDestroy', () => {
    // 清除定时器
    clearInterval(timerId);

    // 取消Observable订阅
    subscription.unsubscribe();

    // 移除事件监听
    window.removeEventListener('mousewheel', handleMouseWhell);
  });
}
```

> 如果将`mounted`和`beforeDestroy`分开写，就需要将`timerId`和`subscription`定义到组件的属性上
