from PyQt5.QtWidgets import QMainWindow
from src.graph_widget import GraphWidget
from ui.main_window import Ui_MainWindow


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)  # 设置界面

        # 创建 GraphWidget 实例并设置为中央部件
        self.graph_widget = GraphWidget(self)
        self.setCentralWidget(self.graph_widget)

        # 连接单选框的槽函数
        self.radioButton_move.toggled.connect(self.on_move_mode_selected)
        self.radioButton_addNode.toggled.connect(self.on_add_node_mode_selected)
        self.radioButton_addEdge.toggled.connect(self.on_add_edge_mode_selected)
        self.radioButton_delete.toggled.connect(self.on_delete_mode_selected)

        # 连接按钮的槽函数
        self.pushButton_fromMatrix.clicked.connect(self.on_push_button_from_matrix_clicked)
        self.pushButton_toFile.clicked.connect(self.on_push_button_to_file_clicked)
        self.pushButton_fromFile.clicked.connect(self.on_push_button_from_file_clicked)
        self.pushButton_toMatrix.clicked.connect(self.on_push_button_to_matrix_clicked)

    def on_move_mode_selected(self, checked):
        """
        当选择移动模式的单选按钮状态变更时的槽函数。

        参数:
            checked (bool): 按钮状态。
        """
        if checked:
            self.graph_widget.set_mode("MOVE")

    def on_add_node_mode_selected(self, checked):
        if checked:
            self.graph_widget.set_mode("ADD_NODE")

    def on_add_edge_mode_selected(self, checked):
        if checked:
            self.graph_widget.set_mode("ADD_EDGE")

    def on_delete_mode_selected(self, checked):
        if checked:
            self.graph_widget.set_mode("DELETE")

    def on_push_button_to_file_clicked(self):
        """
        当点击“输出到文件”按钮时的槽函数。
        """
        self.graph_widget.to_file()

    def on_push_button_from_file_clicked(self):
        """
        当点击“从文件导入”按钮时的槽函数。
        """
        self.graph_widget.from_file()

    def on_push_button_to_matrix_clicked(self):
        """
        当点击“输出到邻接矩阵”按钮时的槽函数。
        """
        self.graph_widget.to_matrix()

    def on_push_button_from_matrix_clicked(self):
        """
        当点击“从邻接矩阵生成”按钮时的槽函数。
        """
        self.graph_widget.from_matrix()
