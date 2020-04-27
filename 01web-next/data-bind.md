
# 数据绑定

## 1.表单数据双向绑定

表单值绑定  ``` :value="value"```

```ts
<el-form  :model="userInfo" >
  <el-form-item label="用户名">
    <el-input v-model="userInfo.username" placeholder="请输入用户名"></el-input>
  </el-form-item>
   <el-form-item label="姓名">
    <el-input v-model="userInfo.name" placeholder="请输入姓名"></el-input>
  </el-form-item>
  <el-form-item>
    <el-button type="primary" @click="onSubmit">提交</el-button>
  </el-form-item>
```

**bad**

```ts
userInfo!: UserInfo;
```

**good**

```ts
userInfo: UserInfo = new UserInfo();
```

> 数据绑定的值必须是存在的数据绑定的值必须是存在的,  !非空断言在有些方法中的参数中定义了```func(val: string| undefined | null)```如果传string类型,tslint会报类型不匹配.



```ts
<el-checkbox-group 
    @change="onResponseSubChange($event)" 
    v-model="checkedResponseSubIds">
    <el-checkbox class="evt-checkbox" v-for="resSub in allResponseSubs" :label="resSub.id" :key="resSub.id" :title="resSub.name">
         <span class="label-name">{{ resSub.name }}</span>
    </el-checkbox>
</el-checkbox-group>
```

**bad**

```ts
@Getter('planManager_checkedResponseSubIds')
checkedResponseSubIds!: string[]
```

**good**

```ts
get checkedResponseSubIds() {
    return this.$store.state.planManager.conditions.UpdatecheckedResponseSubIds;
}

set checkedResponseSubIds(value: string[]) {
    this.$store.dispatch(eventNames.planManager.UpdatecheckedResponseSubIds, value);
}
```
> 在vuex里面的数据需进行双向绑定时, vuex的state管理的值不能直接在组件内更新，设置需设置改变量的get和set方法，变更的时候更新vuex的状态



## 2. 文本插值  {{text}}

 **bad**
 
```ts
<div >
    {{ otherSymptoms.map((item: any) => item.name).join('、') }}
</div>
```

**good**

```ts
<div > {{ symptomsStr }} </div>
```

```ts
get symptomsStr () {
   return this.otherSymptoms.map((item: any) => item.name).join('、');
}
```

**bad**

```ts
import timeformat from '@/common/filters/timeformat';
```

```ts
<el-table-column align="center" label="时间" :show-overflow-tooltip="true" >
    <template slot-scope="scope">
        {{timeformat(scope.row.time)}}
    </template>
</el-table-column>
```

**good**

```ts
<el-table-column align="center" label="时间" :show-overflow-tooltip="true" >
    <template slot-scope="scope">
        {{scope.row.time | timeFilter}}
    </template>
</el-table-column>
```

> 1.文本数据绑定支持表达式的写法，但不对推荐在模板写较复杂的表达式
>
> 2.导入的方法不能直接在模板中使用，可以使用过滤器的方式



## 3. 动态参数

```ts
<div :[attributeName]="val"> </div>
```

```ts
<input @[eventName]="handler" />
```

> ```attributeName``` 和 ```eventName``` 可以通过代码设置值如 ```attributeName``` 为**width**或**height**, 
>
> ```eventName```可以设为**foucs** 或 **change**等其它事件名



- class 与style绑定

**bad**

 ```ts
<div>
 	<div v-for="(item, index) in list" :key="index"
    class="item"
 	:class="{'active':item.id === current.id}">
     {{item.name}}
    </div>
</div>
 ```

**good**

```ts
<div>
 	<div v-for="(item, index) in list" :key="index"
 	:class="item.id === current.id ? 'active item': 'item'">
     {{item.name}}
    </div>
</div>
或
<div>
 	<div v-for="(item, index) in list" :key="index"
 	:class="['item', {'active':item.id === current.id}, `item${index}`]">
     {{item.name}}
    </div>
</div>
```



**bad**

```ts
<div :style="{ background-color: activeColor, font-size: `${fontSize}px` }"></div>
```

**good**

```ts
<div :style="{ backgroundColor: activeColor, fontSize: `${fontSize}px` }"></div>
或
<div :style="{ 'background-color': activeColor, 'font-size': `${fontSize}px` }"></div>
```

> 属性名带有段横杠 ’ **-**  ‘ 的需改成camelCase式如: ```backgroundColor```，或使用引号连起来```'background-color'```
