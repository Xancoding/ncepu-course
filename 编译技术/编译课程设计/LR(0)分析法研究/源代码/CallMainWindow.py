import os
import sys

import matplotlib.pyplot as plt
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import *
from graphviz import Digraph

from MainWindow import Ui_MainWindow
from main import *


class MainForm(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainForm, self).__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.open_file_1)
        self.pushButton_2.clicked.connect(self.open_file_2)
        self.lr0 = None

    def open_file_1(self):
        file_name, file_type = QtWidgets.QFileDialog.getOpenFileName(self, "选取文件", os.getcwd(),
                                                                     "Text Files(*.txt)")
        file_name_temp = file_name.split('/')[-1][0:-4]
        language = get_language(file_name=file_name)
        self.lr0 = LR0(language=language, state_num=0, relation_num=0)
        language_extended = self.lr0.extend_language()
        projects = self.lr0.generate_projects()
        state_list, relation_list = self.lr0.generate_dfa()

        dot = Digraph(comment='The Round Table')
        for n in state_list:
            str_temp = 'state ' + str(n.num) + ':\n'
            for sp in n.state_projects:
                str_temp += sp
                str_temp += '\n'
            str_temp = str_temp[:-1]
            if n.is_final_state:
                dot.node(str(n.num), str_temp, shape='doublecircle')
            else:
                dot.node(str(n.num), str_temp, shape='circle')
        for e in relation_list:
            dot.edge(str(e.in_state.num), str(e.out_state.num), label=e.character)
        dot.render('test_output/' + file_name_temp + '_dfa.gv', format='jpg', view=False)  # 生成dfa图
        img_path_dfa = 'test_output/' + file_name_temp + '_dfa.gv.jpg'
        self.showImage = QPixmap(img_path_dfa).scaled(self.label.width(), self.label.height())
        self.label.setPixmap(self.showImage)

        ag_table = self.lr0.create_action_goto_table()
        fig, ax = plt.subplots()
        ax.set_axis_off()
        table = ax.table(
            cellText=ag_table,
            cellLoc="center",
            loc="upper left")
        ax.set_title("ACTION GOTO TABLE",
                     fontweight="bold")
        plt.savefig('test_output/' + file_name_temp + '_agt.png', bbox_inches='tight')  # 生成action——goto表
        img_path_agt = 'test_output/' + file_name_temp + '_agt.png'
        self.showImage_2 = QPixmap(img_path_agt).scaled(self.label_2.width(), self.label_2.height())
        self.label_2.setPixmap(self.showImage_2)

    def open_file_2(self):
        if self.lr0 is not None:
            file_name, file_type = QtWidgets.QFileDialog.getOpenFileName(self, "选取文件", os.getcwd(),
                                                                         "Text Files(*.txt)")
            file_name_temp = file_name.split('/')[-1][0:-4]
            with open(file_name) as f:
                string = f.read()
            analyticable, at = self.lr0.str_analyze(string)  # 生成分析表
            fig, ax = plt.subplots()
            ax.set_axis_off()
            table = ax.table(
                cellText=at,
                cellLoc="center",
                loc="upper left")
            ax.set_title("ANALYSIS TABLE",
                         fontweight="bold")
            plt.savefig('test_output/' + file_name_temp + '_at.png', bbox_inches='tight')  # 生成分析表
            img_path_at = 'test_output/' + file_name_temp + '_at.png'
            self.showImage_3 = QPixmap(img_path_at).scaled(self.label_3.width(), self.label_3.height())
            self.label_3.setPixmap(self.showImage_3)


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = MainForm()
    win.show()
    sys.exit(app.exec_())
