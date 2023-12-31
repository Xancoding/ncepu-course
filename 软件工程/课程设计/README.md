# back-end

[back-end](https://mygitlab.quwancode.com/ShaneXan/api.psychological-counseling.com)

## 安装Redis

运行redis：`redis-server`

## 安装MySQL并运行

## 环境配置

- Java8 + SpringBoot2.5
- 新建一个名为 `db-proj` 的MySQL数据库
- 将 `back-end/db-proj.sql`导入你的 `db-proj` 数据库
- 修改 `src/main/resources/application.yml` 中的 `datasource`，使之与你自己的数据库信息相对应
- 之后就可以运行后端服务器啦
- 可以把 `backend/postman-api` 导入你的 postman，来检查后端接口是否正常运行



# front-end 

[front-end](https://mygitlab.quwancode.com/JiaHui0216/psychological-action)

## 安装Node.js

## 安装包管理工具 yarn

## 安装项目相关依赖

```
yarn install
```

## 启动项目

启动前端服务前请先保证后端服务已经在正常运行

```
yarn serve
```

## 访问 http://localhost:8080/

# 课设要求



1 每个小组，必须根据需求，先设计完项目原型----完成截止时间：2023-10-10；

设计过程中，请和指导老师沟通确认；原型设计平台：[https://modao.cc/brand](https://modao.cc/brand) （每个小组只注册一个账号）

这个环节考察需求分析和设计：占比20%

2 本次协作开发，代码使用平台（[http://mygitlab.quwancode.com/](http://mygitlab.quwancode.com/)）；小组需要创建团队项目，并将成员拉入进来；

可以创建多个项目库（比如，有前端项目，接口项目，可以分开放在2个不同的仓库中）；

3 答辩演示，每个小组，代码开发测试完毕后，在期末进行演示答辩

整个作品评分标准：

1 数据库设计规范性，合理性，数据对象的命名规范性； ---10分；

2 软件架构、代码文件结构组织的规范性，科学性； ----10分；

3 程序书写习惯，变量名的规范性，代码逻辑是否清晰等； ----10分

4 系统功能的完成度，丰富性，最终系统的可用性以及开发工作量；-----30分

可以自行扩展系统的必要功能，使系统的功能更强大；

注意，扩展的功能一定是相关的，适合实际应用场景的；

5 是否规定时间完成（根据代码提交的时间轴和版本）； -------5分；

6 前端规范性及UI界面的美观性 ------10分；

7 软件系统开发设计说明文档-报告； ------10分；

8 代码管理与组织能力，git使用规范性； ------10分；

9 系统的性能，安全等技术特色评估； -------5分；

# 需求场景：心理咨询信息发布与预约系统

设计并实现一个心理咨询信息发布与预约系统，具体需求包括但不限于以下功能：

（1）实现心理咨询师、咨询者两种角色的用户注册功能；

（2）每次咨询时间固定为50分钟，自行设计可选时间段，心理咨询师可从可选时间段中，选择自己可接受咨询的时间，支持设置周期性时间、支持取消已选时间；

（3）咨询者可查看咨询师的信息、咨询师的可选咨询时间，并发起预约申请。申请提交后，需咨询师确认，方可建立预约。同一咨询者可在同一时间段向多个咨询师提交申请，预约建立后，该时间段其他申请自动取消。

（4）预约建立后，咨询师或咨询者均可发起取消预约申请，仅当另一方同意取消预约后，预约方可被取消。

（5）咨询师与咨询者均可在后台查看个人的咨询历史。

---

墨刀参考教程：
https://www.woshipm.com/rp/614989.html
https://modao.cc/hc/articles/196
https://annhanhan.gitbooks.io/mockingbot/content/

---

【题库】
https://note.youdao.com/s/Dy2qLE4z
从题库中选择1项作为本学期课程设计的总体需求，共12项，从中选择1项。

# 后端技术栈

## 必学

Java Web （Maven + Servlet）数据库不用看

Spring （基础 IOC反转控制 AOP面向切片编程）+ Spring MVC （前后端交互） + Mybatis plus （数据库交互）（这个在Java Web 里讲过了） -- SSM 框架

SpringBoot（脚手架）

## 扩展

Spring Security（安全框架）

Redis（缓存数据库） + Spring Cache（中间件）

消息队列：**Rabbit MQ（简单）** | Rocket MQ | Kafka（最快） 

MongoDB（文档型数据库）部署简单，天然支持集群，可以存储非结构化数据 如：JSON

# 前端技术栈

HTML + CSS + JS(TS) + Vue3