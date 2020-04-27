#  数据传递

## 1. 父组件  -> 子组件

**bad**

```ts
@Prop({
    default: {}
})
region!: RescueRegion;
```
**good**

```ts
@Prop({
	default: () => {
        return new RescueRegion();
    }
})
region!: RescueRegion;
```

>如果传个子组件的是复杂类型其默认值必须是一个函数的返回值
>
>父组件改变Prop的值对子组件进行更新，子组件不应该直接更改Prop传入的值如 ```this.regionList = res.data```, 子组件要更新Prop的值可以通过this.$emit('update:prop', val);  但绑定的属性上必须加上
>
>`.sync`语法，如：

```ts
<ResourceList :visible.sync="resListVisible" :resourceList="resourceList"></ResourceList>

<el-dialog
  class="location-dialog clearfix"
  :show-close="false"
  :modal-append-to-body="false"
  :modal="true"
  @close="onClose"
  :visible.sync="visible">
	<div>
        ...
    </div>
</el-dialog>
```

```ts
onClose() {
    this.$emit('update:visible', false);
}
```

- 访问子组件    `ref`

```ts
<div class="login-form">
   <el-form ref="loginForm" :model="form" :rules="rules">
      <el-form-item prop="username" class="login-item" 
      :label="$t('login.username')"
	</el-form>
</div>
```

```ts
public async handleLogin() {
    const form: any = this.$refs['loginForm'];
    lForm.validate(async (valid: any) => {
      if (valid) {
          ...
      }
   	})
}
```

> 在子组件标签上添加ref属性，通过   `this.$refs['loginForm']`   可以拿到子组件的实例，

## 2. 子组件 -> 父组件 ```this.$emit(eventName, val)```

```ts
 /**
 * 行点击
 * @param {RescueRegion} rescueRegion
 * @memberof RegionList
 */
 handleRowClick(rescueRegion: RescueRegion) {
 	this.currentRegion = rescueRegion;
 	this.$emit('row-click', rescueRegion);
 }
```

```ts
<RegionList 
 	:canEdit="false" :list="regionList"
    @row-click="handleClick" 
    @view-details="handleViewDetails"/>
```

- 子组件向  -> 父组件的父组件

> 向上上级组件传值即调用父组件的$emit方法，如: `this.$parent.$emit(eventName, val)；`

## 3. 兄弟组件传值

1. 先子传父，再父传子

**父组件**

```ts
<template>
  <div class="visualization-container">
      <MobileMap />
      <ContextMenu :mapType="mapType"/>
      <MapNavigation @may-type-change="mapTypeChange"/>
      <RescueSiteInfo />
      <RescueSiteInfoEdit />
      <RegionSetting />
      <RescueTargetInfo />
  </div>
</template>
```

```ts
mapTypeChange(type: string) {
    this.mapType = type;
}
```

**ContextMenu 子组件**

```ts
@Prop({
    default: 'rescueRegion'
})
mapType!: string;
```
**MapNavigationi子组件**
```ts
handleClick(type: string) {
    this.$emit('may-type-change', type);
}
```

## 4. 通过vuex进行数据共享

> 例如一个表单进行新增成功后另外一个列表组件需要进行列表刷新

**列表组件**

```ts
  @Getter('rescueVisualization_rescueRegions')
  rescueRegionList!: RescueRegion[];
```
**表单组件**
```ts
save() {
    regionSettingService
      .saveRescueRegion(this.rescueRegion)
      .then((res: any) => {
        if (res) {
          notifyUtils.message('保存成功');
          this.$store.dispatch(StoreEvents.RescueVisualization.SetRescueRegions);
        } else {
          notifyUtils.message('保存失败');
        }
      })
      .catch((err: any) => {
        notifyUtils.message('保存失败');
      });
  }
```

**store**

```ts
state: {
    rescueRegions: []
},
mutations: {
    SET_RESCUE_REGIONS: (state: any, payloads: any) => {
    	state.rescueRegions = payloads;
	},  
}
actions: {
    setRescueRegions: async ({ commit }: any) => {
        const rescueRegionList = await regionSettingService.queryRescueRegionList();
        commit('SET_RESCUE_REGIONS', rescueRegionList);
    },
},
getters: {
	rescueVisualization_rescueRegions: (state: any) => state.rescueRegions, 
}
```

## 5. 其它(一些发布订阅的方式，比如rxjs等)

### 5.1 rxevent

**订阅**

```typescript
rxevent.subscribe(RxEventType.PLOTTOOL_ONENDDRAW, 'region-plot-service', (drawElement: any) => {
    elementPlot = drawElement;
    areaMeasure();
    addTooltip();
    plotFinished = true;
    rxevent.unsubscribe(RxEventType.PLOTTOOL_ONENDDRAW, 'region-plot-service');
});
```

**发布**

```typescript
// 标绘完成事件
g2.plot.PlotTool.prototype.onEndDraw = (drawElement: any) => {
    rxevent.publish(RxEventType.PLOTTOOL_ONENDDRAW, drawElement);
};
```

**取消订阅**

```typescript
rxevent.unsubscribe(RxEventType.PLOTTOOL_ONENDDRAW, 'region-plot-service');
```

### 5.2 emitter

```ts
function broadcast(componentName, eventName, params) {
  this.$children.forEach(child => {
    var name = child.$options.componentName;

    if (name === componentName) {
      child.$emit.apply(child, [eventName].concat(params));
    } else {
      broadcast.apply(child, [componentName, eventName].concat([params]));
    }
  });
}
export default {
  methods: {
    dispatch(componentName, eventName, params) {
      var parent = this.$parent || this.$root;
      var name = parent.$options.componentName;

      while (parent && (!name || name !== componentName)) {
        parent = parent.$parent;

        if (parent) {
          name = parent.$options.componentName;
        }
      }
      if (parent) {
        parent.$emit.apply(parent, [eventName].concat(params));
      }
    },
    broadcast(componentName, eventName, params) {
      broadcast.call(this, componentName, eventName, params);
    }
  }
};
```

> tthis.$parent.$emit()可以给上上级组件传值，dispatch方法可以给执行组件名的父组件传值，boradcast是父组件触发指定组件名的子组件$emit()方法