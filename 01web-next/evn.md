# 前端开发环境
<!-- TOC -->

- [前端开发环境](#%E5%89%8D%E7%AB%AF%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83)
    - [基础环境](#%E5%9F%BA%E7%A1%80%E7%8E%AF%E5%A2%83)
    - [开发工具](#%E5%BC%80%E5%8F%91%E5%B7%A5%E5%85%B7)
    - [插件](#%E6%8F%92%E4%BB%B6)
        - [vscode插件](#vscode%E6%8F%92%E4%BB%B6)
        - [chrome插件](#chrome%E6%8F%92%E4%BB%B6)

<!-- /TOC -->

## 基础环境

```js
1. node  // 保证前端开发人员node版本及npm版本一致
2. Pyhton2.7x  // 编译些npm包必要环境
```
配置全局客户端私有 CNPM 仓库源地址
> 使用指令npm config edit, 在弹出的文件中加入 `registry=http://172.22.24.36:7001/`
  配置完成后,即可通过npm指令安装npm包
   或者，在当前用户文件夹下，创建文件.npmrc（新建文件时，应命名为..npmrc，否则会提示“必须键入文件名”），路径如: C:\Users\xxx\.npmrc。在文件中加入如下内容`registry=http://172.22.24.36:7001/`

## 开发工具

```js
1. vscode  // 尽量保证前端开发人员vscode版本一致，使用官方最新稳定版
2. git-client 类似SmartGit git客户端软件
3. chrome  // 尽量保证前端开发人员chrome版本一致，版本取决于项目要求
```

## 插件

`vscode插件内网安装方式：`
1. 在外网vscode安装后，拷贝C:\Users\xxx\.vscode\extensions文件夹下的内容
2. 覆盖内网机器 C:\Users\xxx\.vscode\extensions 内容即可

使用插件主要目的：
1. 为开发提供便捷操作，提升开发效率
2. 格式化代码，保证代码风格统一

### vscode插件
1. EditorConfig for VS Code，主要用来格式化文件
推荐配置如下：
``` js
root = true

[*]
charset = utf-8 // 设置字符集
indent_style = space // 缩进风格，可选"space"、"tab"
indent_size = 2  // 缩进的空格数
end_of_line = lf  // 结尾换行符,可选"lf"、"cr"、"crlf"

[*.{md,markdown}]
max_line_length = off  // 一行最大长度
insert_final_newline = true // 在文件结尾插入新行
trim_trailing_whitespace = false // 删除一行中的前后空格

[*.js]
insert_final_newline = false
trim_trailing_whitespace = true

[*.json]
insert_final_newline = true
trim_trailing_whitespace = false

[*.{java,cs}]
indent_style = space
indent_size = 4
insert_final_newline = true
trim_trailing_whitespace = true
max_line_length = 140

[*.gradle]
indent_style = space
indent_size = 4
insert_final_newline = true
trim_trailing_whitespace = true

[*.yml]
insert_final_newline = true
trim_trailing_whitespace = true

[*.ts]
insert_final_newline = true
trim_trailing_whitespace = true

```

2. Prettier - Code formatter
主要用来格式化代码，
推荐配置如下：
```js
{
  "singleQuote": true, // 使用单引号代替双引号
  "semi": true,  // 句尾添加分号
  "printWidth": 140,  // 超过140个字符换行
  "tabWidth": 2, // 缩进字节数
  "trailingComma": "none", // 在对象或数组最后一个元素后面是否加逗号
  "bracketSpacing": true  // 在对象，数组括号与文字之间加空格 "{ foo: bar }"
}
```
`注意：Prettier与editconfig对文件代码约束有重复地方，应该以editconfig配置优先，来调整Prettier配置以适配`

3. tslint
主要用来校验静态代码质量，快速发现本地代码质量问题
推荐配置如下，规则说明详细见官网[tslint-rules](https://palantir.github.io/tslint/rules/)
```js
{
  "defaultSeverity": "warning",
  "extends": [],
  "linterOptions": {
    "exclude": [
      "node_modules/**"
    ]
  },
  "rules": {
    "no-debugger": true,  // 不允许使用debugger
    "quotemark": [true, "single"], // 引号的使用规则,只能用单引号
    "interface-name": false, 
    "ordered-imports": false,
    "object-literal-sort-keys": false,
    "no-consecutive-blank-lines": false,
    "trailing-comma": false,
    "arrow-return-shorthand": true,
    "callable-types": true,
    "class-name": true,
    "comment-format": [
      true,
      "check-space"
    ],
    "curly": true,
    "deprecation": false,
    "eofline": true,
    "forin": true,
    "import-blacklist": [
      true,
      "rxjs/Rx"
    ],
    "import-spacing": true,
    "indent": [
      true,
      "spaces"
    ],
    "interface-over-type-literal": true,
    "label-position": true,
    "max-line-length": [
      true,
      140
    ],
    "member-access": false,
    "member-ordering": [
      true,
      {
        "order": [
          "static-field",
          "instance-field",
          "static-method",
          "instance-method"
        ]
      }
    ],
    "no-arg": true,
    "no-console": [
      true,
      "debug",
      "time",
      "timeEnd",
      "trace",
      "info"
    ],
    "no-construct": true,
    "no-duplicate-super": true,
    "no-empty": false,
    "no-empty-interface": true,
    "no-eval": true,
    "no-inferrable-types": [
      true,
      "ignore-params"
    ],
    "no-misused-new": true,
    "no-non-null-assertion": true,
    "no-string-literal": false,
    "no-string-throw": true,
    "no-switch-case-fall-through": true,
    "no-trailing-whitespace": true,
    "no-unnecessary-initializer": false,
    "no-unused-expression": true,
    "no-use-before-declare": false,
    "no-var-keyword": true,
    "one-line": [
      true,
      "check-open-brace",
      "check-catch",
      "check-else",
      "check-whitespace"
    ],
    "prefer-const": true,
    "semicolon": [
      true,
      "always"
    ],
    "triple-equals": [
      true,
      "allow-null-check"
    ],
    "typedef-whitespace": [
      true,
      {
        "call-signature": "nospace",
        "index-signature": "nospace",
        "parameter": "nospace",
        "property-declaration": "nospace",
        "variable-declaration": "nospace"
      }
    ],
    "unified-signatures": true,
    "variable-name": false,
    "whitespace": [
      true,
      "check-branch",
      "check-decl",
      "check-operator",
      "check-separator",
      "check-type"
    ],
    "radix": true,
    "no-bitwise": true
  }
}
```
`注意：tslint与Prettier对文件代码约束有重复地方，应该以Prettier配置优先，来调整tslint配置以适配`

4. Document This(非必须), 为代码生成注释

```js
Ctrl+Alt+D and again Ctrl+Alt+D

Generates documentation for whatever the caret is on or inside of.
```
5. Debugger for Chrome(非必须)， vscode断点调试工具
```
{
    "version": "0.1.0",
    "configurations": [
        {
            "name": "Launch localhost",
            "type": "chrome",
            "request": "launch",
            "url": "http://localhost/mypage.html",
            "webRoot": "${workspaceFolder}/wwwroot"
        },
        {
            "name": "Launch index.html",
            "type": "chrome",
            "request": "launch",
            "file": "${workspaceFolder}/index.html"
        },
    ]
}
```

6. npm Intellisense(非必须), 依赖便捷导入工具.

### chrome插件

1. Postman(非必须)，调试服务端API工具