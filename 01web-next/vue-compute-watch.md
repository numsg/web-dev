---
title: Vue Compute & Watch
created: '2020-04-24T09:32:21.842Z'
modified: '2020-04-27T05:38:59.307Z'
---

# Vue Compute & Watch

## 1. Compute
在绑定到界面的属性需要做转换时需要使用`compute`，不应该在模板中写表达式。在模板中放入太多逻辑会让模板过重且难以维护

```html
// bad
<div>
  {{ user.firstName + ' ' + user.lastName }}
</div>
```

这种转换逻辑要写在计算属性中，界面上直接绑定`fullName`属性即可。
```ts
get fullName(): string {
  return `${this.user.firstName} ${this.user.lastName}`;
}
```
> Vue Class Component中，`compute`属性为`get`方法

计算属性是基于它们的响应式依赖进行缓存的。只在相关响应式依赖发生改变时它们才会重新求值。上面的例子中，只有当`firstName`或`lastName`发生变化时，才会重新计算`fullName`。没有变化时则直接返回之前的计算结果。

## 2. Watch
当你有一些数据发生变化后要执行异步或开销大的方法时，才需要使用`watch`。其它情况下使用`compute`。


例如`typeId`发生变化后要重新查询服务获取数据，可以使用`Watch`
```ts
typeId = 0;

@Watch('typeId')
typeIdChanged(newTypeId: string) {
  service.getOtherData(newTypeId).then((data) => {
    // do somethings
  });
}
```


例如`text`属性绑定到`<input>`上，变化频率可能会非常高，需要截流时，可以使用`watch`
```ts
text = '';
count = 0;

debounceTextChanged!: () => void;

created() {
  this.debounceTextChanged = _.debounce(() => {
    this.count = newText.length;
  }, 500)
}

@Watch('text')
textChanged(newText: string) {
  if (this.debounceTextChanged) {
    this.debounceTextChanged();
  }
}
```

如果要`watch`对象中的某个属性，需要设置`deep: true`
```ts
user = {
  name: ''
};

@Watch('user', { deep: true })
nameChanged() {
  // do somethings
}
```

