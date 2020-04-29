# Vue Slot

### 1. 当组件模板的一部分内容需要父组件决定时，可以使用`slot`

```html
<!-- child component -->
<div>
  <div>This is Header</div>
  <slot></slot>
</div>
```

```html
<!-- parent component -->
<child-component>
  <!-- slot通过组件的children设置 -->
  <div>This is content</div>
</child-component>
```

最后的渲染结果为
```html
<div>
  <div>This is Header</div>
  <div>This is content</div>
</div>
```

***


### 2. 当父组件不设置`slot`也需要显示默认内容时，可以将默认内容加在`<slot>`标签内
```html
<!-- child component -->
<div>
  <div>This is Header</div>
  <slot>Default content</slot>
</div>
```

```html
<!-- parent component -->
<child-component></child-component>
```

最后的渲染结果为
```html
<div>
  <div>This is Header</div>
  <div>Default content</div>
</div>
```

***


### 3. 当有多个`<slot>`时，可以给每个`<slot>`命名
```html
<!-- child component -->
<div>
  <slot name="header"></slot>
  <slot></slot>
  <slot name="footer"></slot>
</div>
```

`<template v-slot>`中的所有内容都将会被传入相应的插槽。任何没有被包裹在带有`v-slot`的`<template>`中的内容都会被视为默认插槽的内容。
```html
<!-- parent component -->
<child-component>
  <template v-slot:header>
    <div>This is Header</div>
  </template>
  <div>This is Content</div>
  <p>And another one.</p>
  <template v-slot:footer>
    <div>This is Footer</div>
  </template>
</child-component>
```

建议在有多个`<slot>`时，使用完整写法，这样更明确一些。
```html
<!-- parent component -->
<child-component>
  <template v-slot:header>
    <div>This is Header</div>
  </template>

  <template v-slot:default>
    <div>This is Content</div>
    <p>And another one.</p>
  </template>
  
  <template v-slot:footer>
    <div>This is Footer</div>
  </template>
</child-component>
```
> `v-slot`只能加在`<template>`标签上

***

### 4. `slot="header"`的语法在Vue 2.6.0版本后已经废弃，不建议使用。Vue3.0中不再支持这种语法

```html
<!--  Deprecated -->
<child-component>
  <div slot="header">Header<div>
</child-component>
```

```html
<!-- Good -->
<child-component>
  <template v-slot:header>
    <div>Header<div>
  </template>
</child-component>
```

### 5. 当`<slot>`中需要访问子组件才有的数据时，可以使用`scoped slot`

`current-user`默认显示`firstName`，提供了`slot`来让父组件自定义显示内容。
```html
<!-- current user -->
<div>
  <img :src="user.image">
  <slot :user="user">
    <span>{{ user.firstName }}</span>
  </slot>
</div>
```

父组件是没有`user`属性的，可以使用`slotProps`访问子组件在`<slot>`标签上绑定的属性
```html
<current-user>
  <template v-slot:default="slotProps">
    <span>{{ slotProps.user.firstName }}</span>
    <span>{{ slotProps.user.lastName }}</span>
  </template>
</current-user>
```
