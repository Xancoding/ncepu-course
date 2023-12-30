import re

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMessageBox

from ui.add_edge_dlg import Ui_addEdgeDlg


def _validate_string(input_str):
    # 去除空格并按逗号分割字符串
    input_str = input_str.replace(' ', '')
    pattern = r'^[a-z]+\s*(,\s*[a-z]+\s*)*$'  # 正则表达式模式：逗号隔开的小写字母
    if re.match(pattern, input_str):
        # 字符串匹配模式，是由逗号隔开的小写字母
        return input_str.split(',')
    else:
        # 如果不匹配，报错
        return []


class AddEdgeDlg(QtWidgets.QDialog, Ui_addEdgeDlg):
    def __init__(self, graph_widget):
        super().__init__()
        self.setupUi(self)

        self.graph_widget = graph_widget

    def accept(self):
        # 获取对话框中用户输入的边信息
        source_node = self.lineEdit_stA.text()  # 获取起点输入框中的信息，必填
        dest_node = self.lineEdit_edA.text()  # 获取终点输入框中的信息，必填
        input_list_str = self.lineEdit_inputA.text()  # 获取第一个输入输入框中的信息，正向边信息，必填
        re_input_list_str = self.lineEdit_inputB.text()  # 获取第二个输入输入框中的信息，反向边信息

        # 检查用户输入的边信息是否合法
        if not source_node.isupper() or not dest_node.isupper():
            # 起点和终点必须是单个大写字母
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("起点和终点必须是单个的大写字母！")
            error_dialog.exec_()
            self.close()
            return
        if source_node == "" or dest_node == "" or input_list_str == "":
            # 起点、终点和正向边信息不能为空
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("起点、终点和正向边信息不能为空！")
            error_dialog.exec_()
            self.close()
            return
        if (not self.graph_widget.check_if_node_exist(source_node)
                or not self.graph_widget.check_if_node_exist(dest_node)):
            # 起点或终点必须存在
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("输入的点不存在，请重新输入！")
            error_dialog.exec_()
            self.close()
            return

        input_list = _validate_string(input_list_str)  # 检查正向边信息是否合法
        re_input_list = []
        if re_input_list_str != "":
            re_input_list = _validate_string(re_input_list_str)  # 检查反向边信息是否合法

        if input_list == [] or (re_input_list_str != "" and re_input_list == []):
            # 正向边信息或反向边信息不合法
            error_dialog = QMessageBox()
            error_dialog.setIcon(QMessageBox.Warning)
            error_dialog.setWindowTitle("Error")
            error_dialog.setText("输入的边信息必须是逗号隔开的小写字母！")
            error_dialog.exec_()
            self.close()
            return

        # source_node < dest_node，如 'A' < 'B'
        if source_node > dest_node:
            source_node, dest_node = dest_node, source_node
            input_list, re_input_list = re_input_list, input_list

        self.graph_widget.add_edge(source_node, dest_node, input_list, re_input_list)
        self.close()
