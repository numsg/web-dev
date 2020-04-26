# 工程结构说明

``` shell
xxx-web
├── dist                                 构建的目标dist目录
│   ├── fonts                            字体图标文件
│   ├── img                              用于webpack打包用到的图片
│   ├── js                               打包后的js文件
│   ├── themes                           换肤相关的样式文件
│   ├── config.json                      应用配置信息
│   ├── favicon.ico                      站点图标
│   └── index.html                       静态主页
├── doc                                  项目相关文档输出
│   └── skin
├── scripts                              项目构建目录
│   ├── gulp                             gulp脚本
│   │   ├── gulp-build.js                    -build脚本
│   │   ├── gulp-docker.js                   -生成docker镜像脚本
│   │   ├── gulp-lint.js                     -做lint检查相关脚本
│   │   ├── gulp-tag-docker.js               -为镜像打tag相关脚本
│   │   └── gulp-config.js                   -执行gulp脚本相关配置文件
│   ├── k8s                              k8s相关配置及脚本
│   │   └── xxx-web.yaml                     -yaml配置文件主要用于持续部署等                   
│   ├── docker                           docker相关配置及脚本
│   │   ├── DockerFile                       -镜像制作配置文件
│   │   └── build.tar                        -镜像制作中间文件
├── public                               静态资源目录
│   ├── themes                           换肤用到的所有样式及图片输出目录
│   ├── config.json                      应用配置信息 
│   ├── favicon.ico                      站点图标
│   └── index.html                       静态主页   
├── src                                  源文件目录
│   ├── api                              服务访问目录  命名约定xxx-service
│   ├── assets                           公共资源，此处资源import使用，是会被webpack打包编译的资源
│   │   ├── fonts                            -字体
│   │   ├── icons                            -小图标
│   │   ├── imgs                             -图片
│   │   └── styles                           -全局样式文件
│   ├── common                           公共代码
│   │   ├── constants                        -常量定义
│   │   ├── directives                       -公用指令
│   │   ├── enums                            -公用枚举
│   │   ├── events                           -公用事件名称
│   │   ├── filters                          -公用过滤器
│   │   └── url                              -公用服务访问url定义
│   ├── components                       公共组件，项目内公共使用的模块
│   ├── lang                             国际化词条，多语言文件
│   │   ├── en-US.json                          -英文词条
│   │   ├── es-EC.json                          -西语词条
│   │   ├── index.ts                           -i18n处理
│   │   └── zh-CN.json                          -中文词条
│   ├── models                           客户端实体对象，命名约定xxx-info
│   ├── router                           全局路由控制
│   ├── skin                             皮肤处理目录
│   ├── store                            状态管理器目录，分模块
│   │   ├── modules                      分模块状态管理器
│   │   ├── getters.ts                   各模块状态state统一导出
│   │   └── index.ts                     store初始化及导出
│   ├── utils                            通用帮助组件
|   ├── ├── ipc
|   ├── │   ├── ipc-event-type.ts        elctron主进程与vue渲染进程通讯事件集合
|   ├── │   └── ipc-renderer.ts          渲染进程ipc控制文件   
│   │   ├── appconfig.ts                 应用配置初始化类
│   │   ├── event.ts                     vue消息管道(使用了vuex后不建议使用eventbus)
│   │   └── validate.ts
│   ├── views                            业务视图组件，原则上尽量扁平化，层次不要太深。如超过10个视图的项目，可以再考虑子目录
│   │   ├── dabout
│   │   │   ├── about.scss               组件样式文件，建议独立
│   │   │   ├── about.vue                组件vue文件，建议template与ts可以并存于此文件。也可依据实际情况将ts分离
│   │   │   └── zh-CN.json                  国际化词条文件，研发时。 构建时会通过gulp统一进行合并到lang目录
│   │   ├── dashboard                    同上。。。 
│   │   │   ├── dashboard.scss
│   │   │   ├── dashboard.vue
│   │   │   └── zh-CN.json
│   │   ├── electron                     vue和electron交互业务组件示例 
│   │   │   ├── eletron-view.vue         
│   ├── App.vue                          vue根组件
│   ├── main.ts                          vue根启动入口
│   ├── shims-tsx.d.ts                   tsx的ts声明文件
│   └── shims-vue.d.ts                   vue的ts声明文件
├── tests                                单元测试目录
│   └── unit
├── themes                               换肤使用的样式文件
│   ├── black
│   └── white
├── .browserslist                        指定目标浏览器的范围
├── .editorconfig                        editorconfig配置
├── .gitignore                           gitignore配置
├── .prettierrc.json                     prettie配置
├── package-lock.json                    package锁定版本文件
├── package.json                         npm包配置文件
├── postcss.config.js                    css插件配置
├── README.md                            项目md文件
├── tsconfig.json                        ts配置文件
├── tslint.json                          ts静态质量检查配置文件
└── vue.config.js                        vue配置文件，vue-cli3简化了原有版本webpack相关所有配置信息，提供了默认配置，如果需要自定义部分配置，可使用此文件进行全局处理
```  

[工程规范](./project-style.md)