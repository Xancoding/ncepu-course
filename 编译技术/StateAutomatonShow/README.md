# 自动机的状态转换图表示 
## 项目简介
本项目是一个用于绘制自动机状态转换图的程序，详细说明见[文档](./documents/编译课程设计报告模版.doc)。  
本项目的代码逻辑参考[这个项目](https://github.com/wineee/StateAutomatonShow)的代码实现。

## 文件目录
```
- documents/：存放文档
- files/：存放导出的`*.graph`文件
- src/： 放自定义的逻辑代码文件，继承 ui/ 下的类
  - dlg/：对话框类
    - add_edge_dlg.py：添加边对话框类
    - add_node_dlg.py：添加节点对话框类
    - matrix_dlg.py：状态转换矩阵对话框类
  - element/：元素类
    - edge.py：边类
    - node.py：节点类
  - abstract_automata.py：自动机抽象类
  - graph_widget.py：图形界面类
  - main_window.py：主窗口类
- ui/：用于存放由Qt Designer转换的UI类代码
- main.py：程序入口主文件
- README.md：说明文档
- requirements.txt：依赖文件
```

## 程序运行
- 运行环境：Python 3.12.0
- 安装依赖：`pip install -r requirements.txt`
- 运行命令：`python main.py`

## 演示视频
https://www.loom.com/share/f63cd57a732849999d92f1d79ea59d27
