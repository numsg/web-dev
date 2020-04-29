# Vuex

使用Vuex的场景
* 当有多个组件要共享数据，更新数据后相关页面都要变化。
* 一个复杂页面拆分成多个且有嵌套层级的子组件时，一层一层传递`props`很麻烦。


例如警情处置组件比较复杂，拆分成了多个子组件，还有子路由。将警情信息放入`store`中就不用在多个组件传递数据，只需要从`store`中获取并展示。
```html
<div class="incident-disposal">
  <SideMenu></SideMenu>

  <router-view></router-view>

  <div>
    <IncidentCard></IncidentCard>
    <IncidentTimeSheet></IncidentTimeSheet>
  </div>
</div>
```


一个简单的store例子
```ts
const store = new Vuex.store({
  state: {
    count: 0
  },
  getters: {
    doubleCount(state) {
      return state.count * 2;
    }
  }
  mutations: {
    setCount(state, count) {
      state.count = count;
    }
    increase(state) {
      state.count += 1;
    },
    decrease(state) {
      state.count -= 1;
    }
  },
  actions: {
    async getCount(context) {
      const count = await axios.get('http://xxxx');
      context.commit('setCount', count);
    }
  }
})
```

### State
* 简单对象，用于存储数据
* 最好在store初始化好所有所需属性。

### Getter
* 是vuex里的计算属性

### Mutation
* 修改`state`的唯一方法就是提交`mutation`
* `mutation`必须是同步函数
* `mutation`的方法名是`mutation type`，通过`store.commit('increase')`来提交`mutation`
* `mutation`的第一个参数为`state`。第二个可选参数为`payload`，通过`store.commit('setCount', 3)`传入额外参数

### Action
* `action`可以包含任意异步操作
* `action`修改`state`需要提交`mutation`，`context.commit('setCount', count)`
* `action`的方法名是`action type`，通过`store.dispatch('getCount')`来执行`action`
* `action`方法的第一个参数为`context`。第二个可选参数为`payload`，通过`store.dispatch('getCount', args)`传入额外参数
  * `context.dispatch`用于执行其它`action`
  * `context.commit`用于递交`mutation`
  * `context.state`当前`module`的`state`
  * `context.getters`当前`module`的`getters`
  * `context.rootState`根`state`
  * `context.rootGetters`根`getters`


## 如何在组件中使用
通过`this.$store`拿到`store`
```ts
@Component
export default class Counter extends {
  get count() {
    return this.$store.state.count;
  }

  get doubleCount() {
    return this.$store.state.getters.doubleCount;
  }

  mounted() {
    this.$store.dispatch('getCount');
  }

  increase() {
    this.$store.commit('increase');
  }

  decrease() {
    this.$store.commit('decrease');
  }
}
```

使用`vuex-class`注解
```ts
import { State, Getter, Mutation, Action } from 'vuex-class';

@Component
export default class Counter extends {
  @State(state => state.count)
  count!: number;

  @Getter('doubleCount')
  doubleCount!: number;

  @Mutation('increase')
  increase! () => void;

  @Mutation('decrease')
  decrease! () => void;

  @Action('getCount')
  getCount! () => Promise<void>;

  mounted() {
    this.getCount();
  }
}
```


## 使用常量替代`Mutation`和`Action`事件类型
`mutation`和`action`的方法名可以使用`ES2015`风格的计算属性命名功能来使用一个常量作为函数名
```ts
export const SOME_MUTATION = 'SOME_MUTATION';
export const SOME_MUTATION = 'SOME_ACTION';
```

```ts
mutations: {
  [SOME_MUTATION](state) {
    // mutate state
  }
},
actions: {
  [SOME_ACTION](context) {
    // action
  }
}
```

```ts
store.commit(SOME_MUTATION);
store.dispatch(SOME_MUTATION);
```

* 可以避免一些编译时无法检查到的错误，例如定义时使用`getIncident`，使用时用`getIncidnet`。
* 可以在定义和使用间建立引用关系，方便在编译器中导航。
