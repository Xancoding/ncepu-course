# web-back-end

- Java8 + SpringBoot2.5
- 新建一个名为 `web-proj` 的MySQL数据库
- 将 `web-proj.sql`导入你的 `web-proj` 数据库
- 修改 `src/main/resources/application.yml` 中的 `datasource`，使之与你自己的数据库信息相对应
- 之后就可以运行后端服务器啦
- 可以把 `postman-api` 导入你的 postman，来检查后端接口是否正常运行
- 与此同时，运行后端服务器后，还可以通过访问 http://localhost:8888/swagger-ui/index.html ，来查看Swagger自动生成的 api 说明文档

# web-front-end
- 安装Node.js
- 安装包管理工具npm
- 在 `web-front-end` 文件夹下执行下述命令：
  ```
  npm insatll 
  npm run dev
  ```
- 之后就正常运行，访问 http://localhost:5173/ 来获取服务



# 视频演示

https://www.loom.com/share/c0cec73076374d4b8c153b97b196afee?sid=7798ac26-eb3e-4a2d-89a4-99317fda0eed
