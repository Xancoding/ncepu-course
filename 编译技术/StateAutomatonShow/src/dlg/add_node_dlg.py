from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMessageBox

from ui.add_node_dlg import Ui_addNodeDlg


# 增加节点对话框
class AddNodeDlg(QtWidgets.QDialog, Ui_addNodeDlg):
    def __init__(self, graph_widget, mouse_x, mouse_y):
        super().__init__()
        self.setupUi(self)

        self.graph_widget = graph_widget
        self.mouse_x = mouse_x
        self.mouse_y = mouse_y

    # 点击确定按钮时的槽函数
    def accept(self):
        # 获取对话框中用户输入的节点信息
        node_name = self.lineEdit_name.text()
        is_initial_state = self.checkBox_initialState.isChecked()
        is_final_state = self.checkBox_finalState.isChecked()
        is_middle_state = self.checkBox_middleState.isChecked()

        # 根据用户选择设置节点状态
        if is_initial_state and is_final_state and not is_middle_state:
            node_state = 3  # 既是初态又是终态
        elif is_initial_state and not is_final_state and not is_middle_state:
            node_state = 1  # 初态
        elif is_final_state and not is_initial_state and not is_middle_state:
            node_state = 2  # 终态
        elif is_middle_state and not is_initial_state and not is_final_state:
            node_state = 0  # 中间态
        else:
            # 不正确的状态，弹出错误提示框
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("不正确的状态！")
            error_dialog.exec_()
            self.close()  # 关闭对话框
            return

        if node_name == "":
            # 节点名称不能为空
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("节点名称不能为空！")
            error_dialog.exec_()
            self.close()
            return

        if not node_name.isupper():
            # 节点名称必须是单个大写字母
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("节点名称必须是单个的大写字母！")
            error_dialog.exec_()
            self.close()
            return

        if self.graph_widget.check_if_node_exist(node_name):
            # 节点名称不能重复
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("节点名称不能重复！")
            error_dialog.exec_()
            self.close()
            return

        # 在 graph_widget 中添加新节点，使用用户提供的信息
        self.graph_widget.add_node(node_name, node_state, self.mouse_x, self.mouse_y)
        self.close()  # 关闭对话框
