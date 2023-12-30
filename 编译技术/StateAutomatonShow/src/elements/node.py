from PyQt5.QtCore import QRectF, Qt
from PyQt5.QtGui import QPainterPath, QPen
from PyQt5.QtWidgets import QGraphicsItem


class Node(QGraphicsItem):
    def __init__(self, graph_widget, name, node_state=0):
        """
        Node的构造函数。

        参数:
            graph_widget (GraphWidget): 父图形小部件。
            name (str): 节点的名称。
            node_state (int): 节点状态（0: 中间态，1: 初始态，2: 终止态，3：初态和终态）。
        """
        super().__init__()

        # 保存父图形小部件
        self.graph = graph_widget

        # 节点的名称和状态
        self.m_nodeName = name
        self.m_nodeState = node_state

        # 设置节点大小和边界矩形
        self.node_size = 30
        self.inner_circle_size = 20
        self.adjust = 2  # 用于边界矩形的调整
        self.bounding_rect = QRectF(-20 - self.adjust, -20 - self.adjust, 46 + self.adjust, 46 + self.adjust)

    def boundingRect(self):
        """
        返回节点的边界矩形。
        """
        return self.bounding_rect

    def shape(self):
        """
        返回节点形状（椭圆）的 QPainterPath。
        """
        path = QPainterPath()
        path.addEllipse(-self.node_size // 2, -self.node_size // 2, self.node_size, self.node_size)
        return path

    def paint(self, painter, option, widget):
        """
        根据节点的状态绘制节点的外观。
        """
        # 设置画笔属性
        painter.setPen(QPen(Qt.black, 0))
        painter.setBrush(Qt.white)

        # 绘制表示节点的外部椭圆
        painter.drawEllipse(-self.node_size // 2, -self.node_size // 2, self.node_size, self.node_size)

        # 根据节点状态修改外观
        if self.m_nodeState == 0:
            # 中间态：添加不同的形状或标志
            painter.drawEllipse(-self.node_size // 2, -self.node_size // 2, self.node_size, self.node_size)

        elif self.m_nodeState == 1:
            # 初始状态：添加浅灰色背景
            painter.setBrush(Qt.lightGray)
            painter.drawEllipse(-self.node_size // 2, -self.node_size // 2, self.node_size, self.node_size)

        elif self.m_nodeState == 2:
            # 终止状态：添加内部圆
            painter.drawEllipse(-self.inner_circle_size // 2, -self.inner_circle_size // 2,
                                self.inner_circle_size, self.inner_circle_size)

        elif self.m_nodeState == 3:
            # 初始和终止状态：添加浅灰色背景和内部圆
            painter.setBrush(Qt.lightGray)
            painter.drawEllipse(-self.node_size // 2, -self.node_size // 2, self.node_size, self.node_size)
            painter.drawEllipse(-self.inner_circle_size // 2, -self.inner_circle_size // 2,
                                self.inner_circle_size, self.inner_circle_size)

        # 绘制节点名称
        text_rect = QRectF(-self.node_size // 2, -self.node_size // 2, self.node_size, self.node_size)
        painter.setPen(Qt.black)
        flags = Qt.TextWordWrap | Qt.AlignCenter
        painter.drawText(text_rect, flags, self.m_nodeName)

    def get_center(self):
        """
        获取节点中心点坐标。
        """
        center_x = self.pos().x()
        center_y = self.pos().y()
        return center_x, center_y
