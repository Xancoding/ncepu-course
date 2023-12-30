import sys

from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QApplication
from qdarkstyle import LightPalette

from src.main_window import MainWindow

import qdarkstyle


if __name__ == "__main__":
    # create the application and the main window
    app = QApplication(sys.argv)
    main_window = MainWindow()

    # setup stylesheet
    app.setStyleSheet(qdarkstyle.load_stylesheet(qt_api='pyqt5', palette=LightPalette()))

    # Set global font
    default_font = QFont("霞鹜文楷 屏幕阅读版 R", 10)
    app.setFont(default_font)

    # run
    main_window.show()
    sys.exit(app.exec_())
