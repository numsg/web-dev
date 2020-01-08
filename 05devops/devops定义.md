devops定义
<!-- TOC -->

- [任务(task)定义](#任务task定义)
- [环境准备plan定义(手动)](#环境准备plan定义手动)
- [持续构建plan定义(自动)](#持续构建plan定义自动)
- [持续交付定义(手动)](#持续交付定义手动)
- [持续部署定义(手动或自动)](#持续部署定义手动或自动)

<!-- /TOC -->

这里是以预案管理项目为例来介绍devops里面一些过程定义，可适用bamboo及jenkins。

## .1. 任务(task)定义

```sh
0. code-review/dependencies
1. compile
2. test
3. report
4. pack
5. push-to-nexus || push-to-habor
6. deploy
```

## .2. 环境准备plan定义(手动)
1. 服务端环境镜像准备
```sh
pms_backend-build-environment
```

2. 前端环境镜像准备
```sh
pms_frontend-build-environment
```

3. 其它环境镜像准备
```sh
pms_[other]-build-environment
```
`注意点`
1. 如果部门的基础镜像已经满足构建需求，则无需创建plan

2. 设置成手动构建，如果构建环境不变，不需要再次手动执行plan

3. push到镜像仓库的镜像应该归属项目组管理

4. 镜像规范应与项目镜像规范保持一致

5. 本应该是静态代码质量坚持完成后，再执行单元测试，但由于执行sonarquber后需要把单元测试产生得报告上传至sonarquber平台，所以将test任务提前。


## .3. 持续构建plan定义(自动)

1. 每次推送代码构建，  plan命名【工程名称》+'_'+build】
```sh
pms-plan-preparation_build任务如下：
0. [dependencies] //按需选择
1. compile
2. test
3. sonarquber
4. pack
```


2. 每日构建，发布开发版，  plan命名【工程名称》+'_'+daily】
```sh
pms-plan-preparation_daily任务如下：
0. [dependencies] //按需选择
1. compile
2. test
3. sonarquber
4. pack
5. push-to-nexus || push-to-habor
```

## .4. 持续交付定义(手动)

1. 发布版本给测试，plan命名【工程名称》+'_'+beta】
```sh
pms-plan-preparation_beta任务如下：
0. [dependencies] //按需选择
1. compile
2. test
3. sonarquber
4. pack
5. push-to-nexus || push-to-habor
```
2. 发布版本给测试，  plan命名【工程名称》+'_'+release】
```sh
pms-plan-preparation_release任务如下：
0. [dependencies] //按需选择
1. compile
2. test
3. sonarquber
4. pack
5. push-to-nexus || push-to-habor
```

## .5. 持续部署定义(手动或自动)
1. 部署到开发环境, plan命名【工程名称》+'_'+deploy-dev】
```sh
pms-plan-preparation_deploy-dev任务如下：
6. deploy
```

2. 部署到开发环境【工程名称》+'_'+deploy-prod】
```sh
pms-plan-preparation_deploy-prod任务如下：
6. deploy
```