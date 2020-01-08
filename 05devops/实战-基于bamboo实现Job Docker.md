实战-基于bamboo实现Job Docker
<!-- TOC -->

- [背景](#背景)
- [方案分析](#方案分析)
    - [方案一](#方案一)
    - [方案二](#方案二)
    - [方案三](#方案三)
    - [未来设想](#未来设想)
- [方案二实践](#方案二实践)
    - [bamboo remote agent准备](#bamboo-remote-agent准备)
    - [基础环境构建](#基础环境构建)
    - [项目软件构建(以持续构建为例)](#项目软件构建以持续构建为例)
        - [每日构建，发布开发版](#每日构建发布开发版)
    - [参考](#参考)

<!-- /TOC -->

## .1. 背景
基于bamboo持续构建，我们的诉求是：
1. 具备基础的持续构建环境(server/serve-agent/remote-agent)
2. 每个代码库构建的环境期望要求agent的环境与开发及生产环境高度保持一致
3. 在有限的资源下能尽量满足团队各种需求的构建
4. 要求构建速度快，能发挥持续构建最大价值
5. 构建任务逻辑清晰，简洁
6. 持续构建是开发人员本质工作之一，形成构建最佳实践后，让开发人员只需要聚焦自己的开发任务，不需关注构建流程

为了达成以上诉求，现有构建存在的问题：
1. 构建agent资源有限，如需拓展，要花钱采购
2. 项目及产品构建环境复杂(如前端需要不同的nodejs环境，后端需要java/.netcore环境)，如果类似环境都部署在一个agent上，构建成果可信度低。
3. 团队用于持续构建硬件资源有限，横向拓展虚拟机用于构建较困难
4. 产品开发团队构建过程定义各不相同，难以统一管理维护

结合12月初公司组织的bamboo培训以及咱们团队一直以来对持续构建的探索，提出了以下几个方案。

## .2. 方案分析

### .2.1. 方案一 

远程命令执行方式，bamboo server远程驱动拥有docker engine能力机器进行持续构建(注：该机器不是bamboo的agent)，整个构建发生在拥有容器环境的容器实例里面，构建完后，自动释放此次构建启动的容器资源。

背景: 此方案是结合咱们目前基于k8s容器开发环境，将持续构建从jenkins迁移到bamboo实现docker-build-in-docker的原始思路落地实践的。

`优点`
1. 不占用agent数量限制资源
2. 构建完成后，docker engine机器运行用于持续构建的容器实例销毁，不占用资源
3. 构建环境在容器里面，由项目组自定义的环境镜像，构建环境干净
4. 项目组能自定义构建环境，满足各种不同需求的构建任务
`缺陷`
1. 构建脚本复杂，难以维护
```shell
docker -H tcp://172.22.3.101:2375 build -t ${bamboo_repository_revision_number} - << EOF
FROM 172.22.3.4/library/alpine-git AS src
WORKDIR /app
RUN git clone http://zongjian:123@172.16.x.x/scm/gspms/pms-plan-preparation.git && \
  cd pms-plan-preparation && \
  git checkout -f ${bamboo_repository_revision_number}

FROM 172.22.3.4/library/openjdk:8 AS build
WORKDIR /src
COPY --from=src /app/pms-plan-preparation .
RUN chmod +x gradlew && ./gradlew test  && ./gradlew sonarqube && ./gradlew build
EOF
```
2. 所有构建任务在一个脚本完成，构建思路不清晰
3. 整个过程不具备bamboo构建风格

该方案已经完成实践，但由于以上一些缺陷，不是最优方案。

### .2.2. 方案二

Job Docker方式，bamboo server调度remote-agent基于docker container方式进行持续构建

背景： 此方案是在19年12月初听了马老针对bamboo培训课程后，更加熟悉bamboo以后，基于Job Docker方式实现容器化持续构建的落地方案。

`优点`
1. 构建完成后，remote-agent机器运行用于持续构建的容器实例销毁，不占用资源
2. 构建环境在容器里面，由项目组自定义的环境镜像，构建环境干净
3. 项目组能自定义构建环境，满足各种不同需求的构建任务
4. 持续构建定义比较符合bamboo构建风格
5. 能清晰看到构建过程中定义的每个任务

`缺陷`
1. 占用agent数量限制资源
2. agent一次只能接受单个plan，即使remote-agent有启动多个互不干扰的容器实例的能力。

### .2.3. 方案三
使用中间件rancher-cli或kubectl调度k8s集群进行构建， bamboo server驱动代理机(或远程机器)使用rancher-cli或kubectl 调用现有私有k8s云平台构建

背景：基于目前bamboo serve不能直接调度agent，并行启动容器实例实现构建，并且bamboo不支持k8s集群作为agent，此方案为过渡方案。

`优点`
1. 构建环境在容器里面，由项目组自定义的环境镜像，构建环境干净
2. 项目组能自定义构建环境，满足各种不同需求的构建任务
3. 能启动多个plan在k8s中进行构建

`缺陷`
1. 持续构建定义不是特别符合bamboo构建风格

### .2.4. 未来设想
k8s作为remote-agent进行构建， bamboo server直接调度现有私有k8s云平台(目前只支持亚马逊)进行构建。`最优方案，但是bamboo暂时不支持。`

背景: 终极方案，可以开发bamboo插件支持，但代价太大。

## .3. 方案二实践
诉求：
1. 现在的产品及项目都是基于容器的，所有构建基本都是基于Job Docker
2. 需要 Job Docker 能力
3. 考虑到异地构建速度问题，agent能遵循就近原则

### .3.1. bamboo remote agent准备
1. 搭建具有容器环境的构建agent虚拟机1台
```sh

```
2. 在bamboo Serve中授权agent

3. 在bamboo Serve中注册agent的能力，在Capabilities里面选项Custom添加Key：location value:wuhan的能力

操作步骤略。

### .3.2. 基础环境构建
1. 准备符合自己项目实际的构建环境镜像
```
比如前端需要镜像具有nodejs环境
后端需要镜像具有jdk环境
```
详细参考[devops定义](./devops定义.md)

### .3.3. 项目软件构建(以持续构建为例)

#### .3.3.1. 每日构建，发布开发版

  1.点击【Create】,选择【Create Plan】.

![1576736531131](.\images\1576736531131.png)



2. 填写 **Project and buid plan name **各项相应信息。其中Plan name详细参考[devops定义](./devops定义.md)

![1576740235793](.\images\1576742326261.png)



3. 填写 **Link repository to new build plan** 各项信息。首先**Repository host** 项选择【Link new reopsitory】,然后在下拉框中再选择【Git】。

![1576742406087](.\images\1576742406087.png)



4. 根据实际填写【Git】的各项信息。注意**Authentication type** 项选择【Username and password】.填写完成并Test connection 成功后，点击【Configut Plan】.

![1576742676024](.\images\1576742676024.png)

5. 点击【Source Code Checkout】，修改其中内容后点击【Save】。

   ![1576804983072](.\images\1576804983072.png)





6. 点击【Add task】，在弹出页面中选择【Script】。![1576743008415](.\images\1576743008415.png)

 

7. 添加  `compile` 任务，填写相应内容后点击【Save】.

```
Task description  的内容为：compile
Script body 的内容为：chmod +x gradlew && ./gradlew compileJava
```
![1576804858431](.\images\1576804858431.png)



8. 参考  6.添加**compile** 任务步骤，依次再添加如下任务：**注意： 任务的顺序不可改变**。

① ` test` 任务：

```
Task description的内容为：test
Script body的内容为：chmod +x gradlew && ./gradlew test
```

  ② `sonarqube` 任务：

```
Task description的内容为：sonarqube 
Script body的内容为：chmod +x gradlew && ./gradlew sonarqube 
```

③ `pack` 任务（打jar包）：

```
Task description的内容为： pack
Script body的内容为：chmod +x gradlew && ./gradlew build 
```

④`pushImage`任务：

```
Task description的内容为： push-to-habor 
Script body的内容为：chmod +x gradlew && ./gradlew pushImage 
```

添加完成后的界面

![1576745227755](.\images\1576745227755.png)



9. (可选)修改Stage的名称,点击【Configure state】，在弹出页面填写相应名称后点击【Save】.

![1576746183943](.\images\1576746183943.png)

![1576746333319](.\images\1576746333319.png)

10. 点击Default Job,在新的页面选择【Requirements】。

![1576746428926](.\images\1576746428926.png)

![1576746627074](.\images\1576746627074.png)

11. 按照下图中的内容填写，然后点击 【Add】，**注意此处内容一定保持与图片中的一样**.

![1576746817863](.\images\1576746817863.png)

![1576747186359](.\images\1576747186359.png)

12. 选择【Docker】,再选择【Docker container】,填写Docker image的内容为 `172.22.3.4/library/openjdk:8`，然后点击【save】.

![1576747707106](.\images\1576747707106.png)

13. 修改Job的名称。点击【Job details】,根据实际项目填写相应内容后，点击【save】。

![1576748073137](.\images\1576748073137.png)

14. 点击【Plan Configuration】页面更新后点击【Triggers】, **注意此处根据实际情况选择trigger**， 由于本示例属于日常构建，所以需要删除 `Repository polling` , 再点击【Add trigger】，选择 `Single daily build` ，填写相应内容后，点击【save trigger】。

![1576748508406](.\images\1576748508406.png)

![1576749125274](.\images\1576749125274.png)

![1576749537614](.\images\1576749537614.png)

![1576749837695](.\images\1576749837695.png)

15. 点击【Actions】，选择【Enable plan】。（如果已是Enable状态，可忽略此步骤）

![1576748319367](.\images\1576748319367.png)

到此结束。

### .3.4. 参考

详细请参考gs—pms，前端pms-web_build，后端pms-plan-preparation_build