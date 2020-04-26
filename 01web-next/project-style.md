# 工程规范（必读）

### 1、注释，使用规则、作用对象、方法描述、参数描述。

* 文件需要注释，需要描述出具体作用
* 共有方法API，必须添加注释，描述方法，描述参数
* 类/成员变量/成员方法应该优先考虑起一个有意义的名字(见名知意), 一个好名字比任何注释都有用, 不要害怕名字长, 长而有意义的名字比短而令人费解的名字好; 
* 应该优化代码结构, 将一些相同功能的代码抽取成方法, 然后起个好名字, 同一个方法内的代码不应该超过80行, 越短越好; 
* 不要试图起一个差的名字, 然后用好的注释去弥补. 好代码(名字) > 坏代码(名字) + 好注释

`添加注释快捷键: Ctrl+Alt+D+D`

``` js
/**
 * 类型定义组件
 *
 * @export
 * @class TypeDefinecontentComponent
 * @extends {Vue}
 */
@Component({
  template: Html,
  style: Styles,
  name: 'el-type-define-content',
  components: {
    'd-data-source-tiled': DDataSourceTiledComponent,
    'el-detail-tree': DetailTreeComponent,
    'el-rule-type': RuleTypeComponent,
  }
})
export class TypeDefinecontentComponent extends Vue {
    /**
   * 平铺 新增数据
   *
   * @param {*} data 数据集
   * @memberof TypeDefinecontentComponent
   */
  async onAddData(data: any) {
    const dataType = this.currentSource.id;
    if (dataType === '102') {
      this.addDistrictLevel(data);
    } else if (dataType === '103') {
      this.addResponseSub(data);
    } else {
      notifyUtil.error(this.$tc('base_data_manage.type_error'));
    }
  }
}

/**
 * 获取所有事件类型
 * odata方式
 * @returns {Promise<any>}
 */
LoadEventTypes(): Promise<any> {
    const q = odataClient({
        service: store.getters.configs.odataUrl,
        resources: 'EventTypeEntity'
    });
    return q.top(1000).get(null).then((response: any) => {
        return this.generateTree(JSON.parse(response.body).value);
    });
}
```

### 2、src/api文件层次结构：
* service少，可以直接平铺在src/api目录下
* 如果超过10个以上service，需要按能力/模块/业务方式进行组织
* 命名小写、中杠隔开、文件后面需要带service、单词+service
``` ts
如: api/base-data-define/event-type-service
```

### 3、文件内引用分级，需要使用Shift+Alt +F 调整格式
* node_modules基础引用
* @gsafety包引用
* 模块引用

不推荐写法
``` ts
import Html from '@/components/plan-manage/history-version/history-version.html';
import odataClient from '@gsafety/odata-client/dist';
import { Vue, Component, Prop, Watch } from 'vue-property-decorator';
import Style from '@/components/plan-manage/history-version/history-version.module.scss';
```
推荐写法
``` ts
import { Vue, Component, Prop, Watch } from 'vue-property-decorator';

import odataClient from '@gsafety/odata-client/dist';

import Html from '@/components/plan-manage/history-version/history-version.html';
import Style from '@/components/plan-manage/history-version/history-version.module.scss';
```


### 4、common/events ，所有的事件名定义都存放在这一个文件中，命名大写
``` js
例如：
/*
*  警情详情发布
*/
const INCIDENT_DETAILS_PUBLISH = 'INCIDENT_DETAILS_PUBLISH';
/**
 * 警情信息
 */
const INCIDENT_DETAILS = 'INCIDENT_DETAILS';

/**
 * 处警事件聚合器
 */
export const DisposalEvents = {
  INCIDENT_DETAILS_PUBLISH,
  INCIDENT_DETAILS
};

``` 

### 5、common/filter
* 用功能命名
* 平铺在filters文件夹下
* 文件的内容与文件名称应有一定关联。

``` js
例如：
-filters
├── data-format.ts   -- 存放所有时间格式处理管道
``` 

### 6、models， 存放实体对象
* 参考第2条（src/api文件层次结构）。

### 7、common/url 
* 参考第2条（src/api文件层次结构）。

### 8、src/utils 
* 工程级别组件，通用方法及组件
* 如配置读取、日志、登录集成、动态菜单，和业务相关的组件。

### 9、src/views

* 页面不需要-view做结尾，命名参考第2条（src/api文件层次结构）。
* 详细参考赵荡整理的 view/components文件夹边界

#### 10. 常量一定要加注释

常量一般是对一些魔法值的抽取, 然后起一个有意义的名字, 做到见名知意, 这里建议对于这种const修饰的常量, 使用全大写命名, 多个单词 _ 分隔, 且常量上面使用/** 注释 */ 说明含义. 

#### 11. import和export命名  

建议import或export时, 变量(const)/实例对象/方法的命名都为小驼峰; class类/interface接口/Vue组件名都为大驼峰。

理由: 参考后端面向对象命名规范, 类/接口等对象都为大驼峰, 而变量/方法/实例对象为小驼峰.

不推荐
```ts
const CellTypeUrl = {
  //
}

export const CellTypeUrl
```
推荐
```ts
const cellTypeUrl = {
  //
}

export const cellTypeUrl
```

#### 12. 开发标记原则   
* TODO 待处理问题
* FIXME 已知有问题的代码    

#### 13. if else控制语句原则 

* 如果 if 后只有一行代码, 也不能省略掉 {} , 省略掉后的可读性非常差...
``` ts
反例
if (...)
  doSomething()

正例
if(...) {
  doSomething()
}
```

* 多个if else if , 可以考虑使用卫语句替代, 如:

``` ts
正例:
if (...) { return ...} 
if(...) { return ... }
反例:
if (...) { ... } else if (...) { ...} else { ...}
```

#### 14. 国际化词条

* 词条的key, 参考AG01的做法统一为大驼峰
* 词条划分, 可以按组件划分(结构清晰, 但会有冗余词条), 或者按系统划分(减少冗余词条, 但使用不方便, 不便于查找维护)
* 词条文件的命名, 建议严格规范命名, zh.json  en.json 不是标准的国际化文件命名
``` ts
命名参考: 
总体：zh-CN.json，en-US.json 
组件：messages-zh-CN.json  messages-en-US.json , 例如：router的router-zh-CN.json、incident-wait的incident-wait-zh-CN.json
```


#### 15. 目录及组件命名  

* 目录名及组件文件名应有意义, 且尽量简短, 如:

```ts
/incident/incident-detail/incident-detail.vue
/api/incident/time-sheet-service.ts  这里为了使文件名尽量简短, 所以就没有命名为incident-time-sheet-service.ts, 因为父目录已经叫incident了, 从路径上是可以知道这个文件的用途的
```

* 组件class名和文件文件名严格一致(class名大驼峰, 文件名 - 分隔), 如:

```ts
shift-change.vue

@Component
export default class ShiftChange extends Vue {
```

* 组件文件如果存在父目录, 且父目录下有且仅有当前一个子组件(今后确定不会增加) , 这时候组件文件名应该和父目录名保持一致, 如:

``` ts
|--- shift-change
|------ shift-change.scss
|------ shift-change.vue
```

*  如同一目录下存在多个兄弟组件, 此时子组件可以根据情况考虑是否携带父目录名, 如

```ts
|--- untreated-list
|------ center-untreated-list.scss
|------ center-untreated-list.vue
|------ seat-untreated-list.scss
|------ seat-untreated-list.vue

|--- layout
|------ navbar.scss
|------ navbar.vue
|------ sidebar.scss
|------ sidebar.vue
```


#### 16. 路由命名  

* 组件引入使用按需加载，需要注明webpackChunkName，引入时定义的名称和组件class名相同
* 路由路径名采用rest风格, 多个单词使用 - 连接;
* 当为多级路由, 且父路由仅用于加载Layout布局时, 其path名应该同子组件的父目录名一致;

```ts
  {
    path: '/incident',  // 警情相关, 由于此处path对应的组件为Layout,仅加载布局用,所以为了和下面的子路由产生一定的关联性,这里使用父级目录名incident作为path
    component: Layout,
    redirect: 'noredirect',
    name: 'Incident',
    icon: 'zujian',
    hidden: true,
    children: [
      {
        path: 'incident-detail',  // 警情详情, 对应目录名incident-detail
        component: () => import(/* webpackChunkName: "IncidentDetail" */  '../views/incident/incident-detail/incident-detail.vue'),
        name: 'IncidentDetail',
        icon: 'wujiaoxing',
        children: [
          {
            path: 'appeal-details', // 接警详情, 对应目录名appeal-details
            component: () => import(/* webpackChunkName: "AppealDetails" */  '../views/incident/appeal-details/appeal-details.vue'),
            name: 'AppealDetails',
            icon: 'wujiaoxing'
          }
        ]
      }
    ]
  },
```

* 路由的name命名为大驼峰, 其后缀正常应该与路由的Path保持一致, 如:

```ts
  {
    path: '/incident-wait',
    name: 'IncidentWait',  // name后缀同path一致,大驼峰命名
    component: () => import(/* webpackChunkName: "IncidentWait" */ '../views/incident/incident-wait/incident-wait.vue'),
    hidden: true
  },
  {
    path: '/untreated-list', // 待处理列表,仅用于加载Layout布局,所以采用子路由组件的父目录名作为path
    component: Layout,
    redirect: 'noredirect',
    name: 'UntreatedList',
    icon: 'zujian',
    children: [
      {
        path: 'center', // 本中心未完成, 最后一级组件名如和上一级有重复, 则路由路径可以考虑去掉重复路径名, 例如此处使用center, 而未使用center-untreated-list
        // 此处untreated-list下面会有多个组件,需要配多个路由,所以这里在组件前加了center前缀作区分
        // 如果untreated-list目录下只有一个路由,那么这里path可以命名为 'index' ,然后该路由组件class类名/组件文件名应同父目录名(untreated-list)保持一致(文件名也可取名index.vue)
        component: () => import(/* webpackChunkName: "CenterUntreatedList" */ '@/views/incident/untreated-list/center-untreated-list.vue'),
        name: 'CenterUntreatedList',
        icon: 'wujiaoxing'
      }
    ]
  },
```

#### 17. 开发顺序(重要)

拆分组件, 确定组件名, 目录名, 目录位置 --- 配置路由, 确定一级路由, 二级路由 --- 实现功能(数据传递, 优先考虑vuex)

#### 18. store里的modules应该加上 -store后缀

#### 19. vue里面的样式都提取出来，写样式时使用嵌套，粒度最少要到功能块。其命名：见名知意和关联性
