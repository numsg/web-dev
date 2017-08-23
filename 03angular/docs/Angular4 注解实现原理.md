# Angular4 注解实现原理

今天我们来了解一下Angular框架中注解实现原理。

在我们使用angular框架进行开发时，我们会定义一些Component、Module,在定义一个Component的时候我们使用的是@Component进行注解声明的，如下代码：

```
@NgModule({
    imports: [
        BrowserModule,
        FormsModule,
        routing
    ],
    declarations: [
        LoginComponent
    ]
})
export class LoginModule {
}

@Component({
     templateUrl: './biz2.component.html'
})
export class Biz2Component {
}
```
这里以@开始的语句和java中的注解的使用方式和作用都非常的类似。@Component的作用就是把相应的元数据添加到备注解的对象（如LoginModule、Biz2Component）中去。那么Angular里的注解是怎么实现的呢？

在了解这之前，我们先要明白[TypScript](https://www.tslang.cn/docs/handbook/decorators.html)中的装饰器。

下面这段源码来自TypeScript官网一个简单装饰器定义的示例，

```
function f() {
    console.log('f(): evaluated');
    return function (target, propertyKey: string, descriptor: PropertyDescriptor) {
        console.log('f(): called');
    };
}

function g() {
    console.log('g(): evaluated');
    return function (target, propertyKey: string, descriptor: PropertyDescriptor) {
        console.log('g(): called');
    };
}

class C {
    @f()
    @g()
    method() { }
}
```

其中f，g函数为装饰器工厂，他们主要作用是根据参数生成特定的装饰器（示例中没有参数，返回的也是特定的装饰器）。f，g函数内部定义的就是具体的装饰器方法，在这些方法中就可以对目标进行各种操作了。

如果你还是不懂，我们可以把这段ts代码编译成js，或许你会马上就明白了。

```
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") {
        r = Reflect.decorate(decorators, target, key, desc);
    }
    else {
        for (var i = decorators.length - 1; i >= 0; i--) {
            if (d = decorators[i]) {
                console.log(d);
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
            }
        }
    }
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
function f() {
    console.log('f(): evaluated');
    return function (target, propertyKey, descriptor) {
        console.log('f(): called');
    };
}
function g() {
    console.log('g(): evaluated');
    return function (target, propertyKey, descriptor) {
        console.log('g(): called');
    };
}
var C = (function () {
    function C() {
    }
    C.prototype.method = function () { };
    return C;
}());
__decorate([
    f(),
    g()
], C.prototype, "method");
```

执行这段js代码 node ./test.js。输出结果如下，
```
f(): evaluated
g(): evaluated
g(): called
f(): called
```

下面我选取Module来分析Angular注解的原理，其它类如：Component，Input也都是类似的。
```
export var /** @type {?} */ NgModule = (makeDecorator('NgModule', {
    providers: undefined,
    declarations: undefined,
    imports: undefined,
    exports: undefined,
    entryComponents: undefined,
    bootstrap: undefined,
    schemas: undefined,
    id: undefined,
}));
```
主要是看makeDecorator里面的实现，

```
export function makeDecorator(name, props, parentClass, chainFn) {
    if (chainFn === void 0) { chainFn = null; }
    var /** @type {?} */ metaCtor = makeMetadataCtor([props]);
    /**
     * @param {?} objOrType
     * @return {?}
     */
    function DecoratorFactory(objOrType) {
        if (!(Reflect && Reflect.getOwnMetadata)) {
            throw 'reflect-metadata shim is required when using class decorators';
        }
        if (this instanceof DecoratorFactory) {
            metaCtor.call(this, objOrType);
            return this;
        }
        var /** @type {?} */ annotationInstance = new ((DecoratorFactory))(objOrType);
        var /** @type {?} */ chainAnnotation = typeof this === 'function' && Array.isArray(this.annotations) ? this.annotations : [];
        chainAnnotation.push(annotationInstance);
        var /** @type {?} */ TypeDecorator = (function TypeDecorator(cls) {
            var /** @type {?} */ annotations = Reflect.getOwnMetadata('annotations', cls) || [];
            annotations.push(annotationInstance);
            Reflect.defineMetadata('annotations', annotations, cls);
            return cls;
        });
        TypeDecorator.annotations = chainAnnotation;
        TypeDecorator.Class = Class;
        if (chainFn)
            chainFn(TypeDecorator);
        return TypeDecorator;
    }
    if (parentClass) {
        DecoratorFactory.prototype = Object.create(parentClass.prototype);
    }
    DecoratorFactory.prototype.toString = function () { return ("@" + name); };
    ((DecoratorFactory)).annotationCls = DecoratorFactory;
    return DecoratorFactory;
}
```

从代码我们可以发现makeDecorator返回的是一个装饰器工厂，这个装饰器工厂会返回一个装饰器TypeDecorator，从而可以知道TypeDecorator中干的就是实现注解的工作：把元数据写入Module修饰的类中去（比如：LoginModule类）

接下来我们进一步分析装饰器TypeDecorator的代码：
```
var /** @type {?} */ TypeDecorator = (function TypeDecorator(cls) {
            var /** @type {?} */ annotations = Reflect.getOwnMetadata('annotations', cls) || [];
            annotations.push(annotationInstance);
            Reflect.defineMetadata('annotations', annotations, cls);
            return cls;
        });
```

TypeDecorator方法内容非常的简单，把@Component传入的参数作为元数据添加到目标类中去。
最后我们可以总结整个注解的实现过程：
1. 使用makeDecorator生成装饰器工厂。
2. 目标类中使用装饰器工厂，并传入相应的参数。
3. 自动调用装饰器方法，把对应的元数据写入annotations属性中去。

这里使用到了一个第三方的库[Reflect](https://github.com/tvcutsem/harmony-reflect/wiki#reflect)，其具体作用就是操作目标类上的元数据。

到这里，Angular注解的机制基本讲完了。

在我们了解了Angular注解的机制后，我们可以动态修改注解，方法如下，
```
@Component({
    selector: "biz2-Component",
    template: "<div></div>"
})
export class Biz2Component {}

const annotations = Reflect.getOwnMetadata('annotations', Biz2Component);
annotations[0].template = "<div>numsg!</div>"
```

这段代码就可以修改AppComponent中的template元数据的内容，达到动态修改的效果。但是要注意任何元数据的修改，改变的只是元数据本身，任何以元数据为基础产生的内容不会修改，比如示例中的代码如果在Biz2Component实例化后的页面内容是没有作用的。这种动态修改的Component只能影响修改后动态创建的组件。






