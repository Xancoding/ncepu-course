# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'matrix_dlg.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MatrixDlg(object):
    def setupUi(self, MatrixDlg):
        MatrixDlg.setObjectName("MatrixDlg")
        MatrixDlg.resize(356, 387)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(MatrixDlg)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.lineEdit_state_set = QtWidgets.QLineEdit(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.lineEdit_state_set.setFont(font)
        self.lineEdit_state_set.setObjectName("lineEdit_state_set")
        self.horizontalLayout.addWidget(self.lineEdit_state_set)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout_2.addLayout(self.horizontalLayout)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_4 = QtWidgets.QLabel(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_4.addWidget(self.label_4)
        self.lineEdit_final_state_set = QtWidgets.QLineEdit(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.lineEdit_final_state_set.setFont(font)
        self.lineEdit_final_state_set.setObjectName("lineEdit_final_state_set")
        self.horizontalLayout_4.addWidget(self.lineEdit_final_state_set)
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_4.addItem(spacerItem1)
        self.verticalLayout_2.addLayout(self.horizontalLayout_4)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_3 = QtWidgets.QLabel(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_3.addWidget(self.label_3)
        self.lineEdit_init_state = QtWidgets.QLineEdit(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.lineEdit_init_state.setFont(font)
        self.lineEdit_init_state.setObjectName("lineEdit_init_state")
        self.horizontalLayout_3.addWidget(self.lineEdit_init_state)
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_3.addItem(spacerItem2)
        self.verticalLayout_2.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_2 = QtWidgets.QLabel(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_2.addWidget(self.label_2)
        self.lineEdit_input_set = QtWidgets.QLineEdit(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.lineEdit_input_set.setFont(font)
        self.lineEdit_input_set.setObjectName("lineEdit_input_set")
        self.horizontalLayout_2.addWidget(self.lineEdit_input_set)
        spacerItem3 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem3)
        self.verticalLayout_2.addLayout(self.horizontalLayout_2)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.pushButton_start_input_f = QtWidgets.QPushButton(MatrixDlg)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton_start_input_f.sizePolicy().hasHeightForWidth())
        self.pushButton_start_input_f.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.pushButton_start_input_f.setFont(font)
        self.pushButton_start_input_f.setObjectName("pushButton_start_input_f")
        self.horizontalLayout_5.addWidget(self.pushButton_start_input_f)
        self.verticalLayout.addLayout(self.horizontalLayout_5)
        self.tableView = QtWidgets.QTableView(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.tableView.setFont(font)
        self.tableView.setObjectName("tableView")
        self.verticalLayout.addWidget(self.tableView)
        self.buttonBox = QtWidgets.QDialogButtonBox(MatrixDlg)
        font = QtGui.QFont()
        font.setFamily("霞鹜文楷 屏幕阅读版 R")
        self.buttonBox.setFont(font)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)
        self.verticalLayout_2.addLayout(self.verticalLayout)

        self.retranslateUi(MatrixDlg)
        self.buttonBox.accepted.connect(MatrixDlg.accept) # type: ignore
        self.buttonBox.rejected.connect(MatrixDlg.reject) # type: ignore
        QtCore.QMetaObject.connectSlotsByName(MatrixDlg)

    def retranslateUi(self, MatrixDlg):
        _translate = QtCore.QCoreApplication.translate
        MatrixDlg.setWindowTitle(_translate("MatrixDlg", "MatrixDlg"))
        self.label.setText(_translate("MatrixDlg", "状态集K      "))
        self.label_4.setText(_translate("MatrixDlg", "终态集Z      "))
        self.label_3.setText(_translate("MatrixDlg", "初态S         "))
        self.label_2.setText(_translate("MatrixDlg", "输入符号表Σ"))
        self.pushButton_start_input_f.setText(_translate("MatrixDlg", "转换函数f"))
