from random import random

from PyQt5 import QtWidgets, QtGui

from src.abstract_automata import AbstractAutomata
from ui.matrix_dlg import Ui_MatrixDlg


# 通过水平表头获取行号
def get_column(model, header):
    for column in range(model.columnCount()):
        item = model.horizontalHeaderItem(column)
        if item and item.text() == header:
            return column
    return -1


# 通过垂直表头获取列号
def get_row(model, header):
    for row in range(model.rowCount()):
        item = model.verticalHeaderItem(row)
        if item and item.text() == header:
            return row
    return -1  # 如果找不到，则返回 -1 或其他指示未找到的值


class MatrixDlg(QtWidgets.QDialog, Ui_MatrixDlg):
    def __init__(self, graph_widget):
        super().__init__()
        self.setupUi(self)
        self.graph_widget = graph_widget  # 保存传入的图形部件
        self.abstract_automata = AbstractAutomata()  # 抽象自动机对象

        self.pushButton_start_input_f.clicked.connect(self.on_push_button_start_input_f)  # 绑定转换函数f按钮的点击事件

    def setup_matrix(self, abstract_automata):
        """
        设置矩阵对话框。

        参数：
        - abstract_automata：抽象自动机对象
        """
        # 根据传入的状态集、输入列表、初始状态和终态集设置 UI 控件
        self.lineEdit_state_set.setText(','.join(abstract_automata.sl_state_set))
        self.lineEdit_input_set.setText(','.join(abstract_automata.sl_input_list))
        self.lineEdit_init_state.setText(','.join(abstract_automata.s_init_state))
        self.lineEdit_final_state_set.setText(','.join(abstract_automata.sl_final_state_set))

        # 设置表格样式
        self.tableView.horizontalHeader().setStyleSheet("QHeaderView::section{background-color:rgb(200, 200, 200)}")
        self.tableView.verticalHeader().setStyleSheet("QHeaderView::section{background-color:rgb(200, 200, 200)}")

        # 设置表格模型
        model = QtGui.QStandardItemModel(len(abstract_automata.sl_state_set), len(abstract_automata.sl_input_list))
        model.setHorizontalHeaderLabels(abstract_automata.sl_input_list)
        model.setVerticalHeaderLabels(abstract_automata.sl_state_set)

        for func in abstract_automata.func_list:
            # 通过行和列的
            row = get_row(model, func.from_state)
            column = get_column(model, func.input_symbol)
            item = QtGui.QStandardItem()
            # 如果单元格中已经有内容，则在原有内容后面添加新的内容
            if model.item(row, column):
                item.setText(model.item(row, column).text() + ',' + func.to_state)
            # 否则，直接设置单元格内容
            else:
                item.setText(func.to_state)

            model.setItem(row, column, item)

        # 下述代码在应用主题时会失效
        # # 行号为初态的行头加斜体
        # for init_state in abstract_automata.s_init_state:
        #     row = get_row(model, init_state)
        #     item = model.verticalHeaderItem(row)
        #     font = item.font()
        #     font.setBold(True)
        #     item.setFont(font)
        #
        # # 行号为终态的行头加下划线
        # for final_state in abstract_automata.sl_final_state_set:
        #     row = get_row(model, final_state)
        #     item = model.verticalHeaderItem(row)
        #     font = item.font()
        #     font.setUnderline(True)
        #     item.setFont(font)

        self.tableView.setModel(model)

    def accept(self):
        """绘制图形"""
        # 清空图形部件
        self.graph_widget.clear()
        # 从 UI 控件中获取状态集、输入列表、初始状态和终态集的文本
        # 状态集K
        state_set = self.lineEdit_state_set.text().split(',')
        state_set = sorted(list(set(state_set)))
        # 输入符号表Σ
        input_list = self.lineEdit_input_set.text().split(',')
        input_list = sorted(list(set(input_list)))
        # 初始状态集S
        init_state = self.lineEdit_init_state.text().split(',')
        init_state = sorted(list(set(init_state)))
        # 终态集Z
        final_state_set = self.lineEdit_final_state_set.text().split(',')
        final_state_set = sorted(list(set(final_state_set)))

        # 生成结点
        for state in list(state_set):
            # 坐标随机生成，范围为 0-500
            x = random() * 500
            y = random() * 500

            node_state = 0  # 中间态
            # node_state (int): 节点状态（0: 中间态，1: 初始态，2: 终止态，3：初态和终态）
            if state in init_state and state in final_state_set:
                node_state = 3
            elif state in init_state:
                node_state = 1
            elif state in final_state_set:
                node_state = 2

            # 生成结点
            self.graph_widget.add_node(state, node_state, x, y)

        # 获取表格模型，生成边
        model = self.tableView.model()
        for row in range(model.rowCount()):
            for column in range(model.columnCount()):
                # 获取单元格的内容
                item = model.item(row, column)
                # 如果单元格内容不为空
                if item:
                    # 通过行和列获取结点的名称
                    from_state = model.verticalHeaderItem(row).text()
                    input_symbol = model.horizontalHeaderItem(column).text()
                    to_state_list = item.text().split(',')
                    # 去重，排序，去除空元素
                    to_state_list = sorted(list(set(to_state_list)))
                    to_state_list = [to_state for to_state in to_state_list if to_state]
                    if not to_state_list:
                        continue

                    # 生成边
                    for to_state in to_state_list:
                        if from_state <= to_state:
                            self.graph_widget.add_edge(from_state, to_state, list(input_symbol), [])
                        else:
                            self.graph_widget.add_edge(to_state, from_state, [], list(input_symbol))

        # 关闭对话框
        self.close()

    def on_push_button_start_input_f(self):
        """生成转换函数f"""
        # 从 UI 控件中获取状态集、输入列表、初始状态和终态集的文本
        state_set = self.lineEdit_state_set.text().split(',')
        input_list = self.lineEdit_input_set.text().split(',')
        init_state = self.lineEdit_init_state.text().split(',')
        final_state_set = self.lineEdit_final_state_set.text().split(',')

        # 放入抽象自动机对象中
        self.abstract_automata.sl_state_set = sorted(list(set(state_set)))
        self.abstract_automata.sl_input_list = sorted(list(set(input_list)))
        self.abstract_automata.s_init_state = sorted(list(set(init_state)))
        self.abstract_automata.sl_final_state_set = sorted(list(set(final_state_set)))

        # 设置表格样式
        self.tableView.horizontalHeader().setStyleSheet("QHeaderView::section{background-color:rgb(200, 200, 200)}")
        self.tableView.verticalHeader().setStyleSheet("QHeaderView::section{background-color:rgb(200, 200, 200)}")

        # 设置表格模型
        model = QtGui.QStandardItemModel(len(self.abstract_automata.sl_state_set),
                                         len(self.abstract_automata.sl_input_list))
        model.setHorizontalHeaderLabels(self.abstract_automata.sl_input_list)
        model.setVerticalHeaderLabels(self.abstract_automata.sl_state_set)

        self.tableView.setModel(model)
