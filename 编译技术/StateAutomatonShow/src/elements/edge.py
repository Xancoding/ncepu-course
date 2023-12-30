from PyQt5.QtWidgets import QGraphicsItem
from PyQt5.QtCore import QPointF, QRectF, Qt, QLineF, QSizeF
from PyQt5.QtGui import QPen, QPainterPath, QFont, QFontMetrics
import math


def _create_line_at_angle(line, angle_degrees, length):
    # 计算线段在指定角度下的向量
    vector = line.p2() - line.p1()
    angle_radians = math.radians(angle_degrees)
    rotated_vector = QPointF(
        vector.x() * math.cos(angle_radians) - vector.y() * math.sin(angle_radians),
        vector.x() * math.sin(angle_radians) + vector.y() * math.cos(angle_radians)
    )
    vector_length = math.sqrt(rotated_vector.x() ** 2 + rotated_vector.y() ** 2)
    normalized_vector = QPointF(rotated_vector.x() / vector_length, rotated_vector.y() / vector_length)
    endpoint = line.p2() + normalized_vector * length  # 在原始线段的终点处创建新线段
    new_line = QLineF(line.p2(), endpoint)
    return new_line


class Edge(QGraphicsItem):
    def __init__(self, graph_widget, source_node, dest_node, input_list, re_input_list):
        """
        初始化 Edge 类的实例。

        参数：
        - graph_widget：GraphWidget 类的实例
        - source_node：边的起始节点名称
        - dest_node：边的目标节点名称
        - input_list：正向边的输入列表
        - re_input_list：反向边的输入列表
        - 起始结点 < 目标结点
        """
        super().__init__()

        # 初始化边的属性
        self.graph = graph_widget
        self.source = self.graph.get_node_by_name(source_node)
        self.dest = self.graph.get_node_by_name(dest_node)
        self.input_list = sorted(list(set(input_list)))
        self.re_input_list = sorted(list(set(re_input_list)))

        self.source_point = QPointF(*self.source.get_center())
        self.dest_point = QPointF(*self.dest.get_center())
        self.arrow_size = 20  # 箭头大小
        self.angle = 150  # 180-箭头与线段的夹角
        self.node_radius = self.source.node_size // 2  # 结点半径
        self.text_rect = None  # 文字矩形
        self.text_font = QFont("霞鹜文楷 屏幕阅读版 R", 10)  # 设置字体和大小
        self.path = QPainterPath()  # 自环路径

    def boundingRect(self):
        # 返回边的边界矩形
        if not self.source or not self.dest:
            # 若起点或终点不存在，返回空的边界矩形
            return QRectF()
        elif self.source == self.dest:
            # 若两节点相同，返回自环的边界矩形，一个预定义的矩形
            return QRectF(self.source_point.x(), self.source_point.y() - 6, 40, 40)
        else:
            # 若两节点不同，返回连线的边界矩形
            return QRectF(self.source_point, self.dest_point).normalized()

    def paint(self, painter, option, widget):
        if not self.source or not self.dest:
            return

        line = QLineF(self.source_point, self.dest_point)
        if line.length() == 0:
            # 若两节点距离为0，绘制自环
            self.path = self._draw_loop_curve(painter)
            self._draw_text_on_arc(painter, self.path, ', '.join(self.input_list))
            return

        # 若两节点距离不为0，绘制连线及箭头
        if self.input_list:
            self._draw_line_and_arrow(painter, line)
            self._draw_text_on_line(painter, line, ', '.join(self.input_list))
        if self.re_input_list:
            self._draw_line_and_arrow(painter, line, True)
            self._draw_text_on_line(painter, line, ', '.join(self.re_input_list), True)

    def _draw_loop_curve(self, painter):
        # 绘制自环曲线
        node_radius = self.source.node_size // 2  # 结点半径
        center = self.source_point  # 计算圆心

        # 计算自环的起点、终点和控制点
        start_point = QPointF(center.x() + node_radius, center.y())
        control_point = QPointF(center.x() + 4 * node_radius, center.y() + 4 * node_radius)
        end_point = QPointF(center.x(), center.y() + node_radius)

        # 绘制自环曲线
        path = QPainterPath()
        path.moveTo(start_point)
        path.quadTo(control_point, end_point)

        pen = QPen(Qt.black, 1, Qt.SolidLine, Qt.RoundCap, Qt.RoundJoin)
        painter.setPen(pen)
        painter.drawPath(path)

        # 绘制自环箭头
        tangent = QPointF(2 * (1 - 0.5) * (control_point.x() - end_point.x()),
                          2 * (1 - 0.5) * (control_point.y() - end_point.y()))

        line = QLineF(end_point + tangent, end_point)
        self._draw_arrow_lines(painter, line)
        return path

    def _draw_line_and_arrow(self, painter, line, is_re=False):
        # 绘制连线
        source_center = self.source.get_center()
        dest_center = self.dest.get_center()

        angle = math.atan2(line.dy(), line.dx())
        if is_re:
            source_line = QPointF(dest_center[0] - self.node_radius * math.cos(angle),
                                  dest_center[1] - self.node_radius * math.sin(angle))
            dest_line = QPointF(source_center[0] + self.node_radius * math.cos(angle),
                                source_center[1] + self.node_radius * math.sin(angle))
        else:
            source_line = QPointF(source_center[0] + self.node_radius * math.cos(angle),
                                  source_center[1] + self.node_radius * math.sin(angle))
            dest_line = QPointF(dest_center[0] - self.node_radius * math.cos(angle),
                                dest_center[1] - self.node_radius * math.sin(angle))

        line = QLineF(source_line, dest_line)
        painter.setPen(QPen(Qt.black, 1, Qt.SolidLine, Qt.RoundCap, Qt.RoundJoin))
        painter.drawLine(line)

        if is_re:
            # 反向箭头，颜色为 Blue
            painter.setPen(QPen(Qt.blue, 1, Qt.SolidLine, Qt.RoundCap, Qt.RoundJoin))
        else:
            # 正向箭头，颜色为 Red
            painter.setPen(QPen(Qt.red, 1, Qt.SolidLine, Qt.RoundCap, Qt.RoundJoin))

        # 绘制箭头
        line_45_1 = _create_line_at_angle(line, self.angle, self.arrow_size)
        painter.drawLine(line_45_1)

        line_45_2 = _create_line_at_angle(line, -self.angle, self.arrow_size)
        painter.drawLine(line_45_2)

    def _draw_arrow_lines(self, painter, line):
        # 绘制箭头线段
        line_45_1 = _create_line_at_angle(line, self.angle, self.arrow_size)
        painter.setPen(QPen(Qt.black, 1, Qt.SolidLine, Qt.RoundCap, Qt.RoundJoin))
        painter.drawLine(line_45_1)

        line_45_2 = _create_line_at_angle(line, -self.angle, self.arrow_size)
        painter.setPen(QPen(Qt.black, 1, Qt.SolidLine, Qt.RoundCap, Qt.RoundJoin))
        painter.drawLine(line_45_2)

    def _draw_text_on_line(self, painter, line, text, is_re=False):
        # 计算文字的中心点
        text_rect = QRectF(QPointF(),
                           QSizeF(QFontMetrics(self.text_font).width(text), QFontMetrics(self.text_font).height()))
        text_rect.moveCenter(line.center())

        # 计算边的角度
        angle = math.atan2(line.dy(), line.dx())
        rotation_degrees = math.degrees(angle)

        # 保存当前状态并设置文字的旋转角度
        painter.save()
        if 0 < rotation_degrees < 90:
            painter.translate(text_rect.center())
            painter.rotate(rotation_degrees)
            painter.translate(-text_rect.center())
        elif 90 < rotation_degrees < 180:
            painter.translate(text_rect.center())
            painter.rotate(rotation_degrees - 180)
            painter.translate(-text_rect.center())
        elif -180 < rotation_degrees < -90:
            painter.translate(text_rect.center())
            painter.rotate(rotation_degrees + 180)
            painter.translate(-text_rect.center())
        else:
            painter.translate(text_rect.center())
            painter.rotate(rotation_degrees)
            painter.translate(-text_rect.center())

        # 根据线段方向调整文本位置
        if is_re:
            vertical_offset = 8
        else:
            vertical_offset = -8
        text_rect.translate(0, vertical_offset)

        # 绘制文字
        painter.setFont(self.text_font)
        painter.drawText(text_rect, Qt.AlignCenter, text)

        self.textRect = text_rect  # 保存文字矩形

        # 恢复之前的状态
        painter.restore()

    def _draw_text_on_arc(self, painter, path, text):
        # 计算圆弧的长度
        arc_length = path.length()

        # 计算圆弧上的位置
        position_on_arc = arc_length / 2  # 文字放置在圆弧的中点
        point_on_arc = path.pointAtPercent(position_on_arc / arc_length)

        # 计算文字矩形
        text_rect = QRectF(QPointF(),
                           QSizeF(QFontMetrics(self.text_font).width(text), QFontMetrics(self.text_font).height()))
        text_rect.moveCenter(point_on_arc)

        # 将文字矩形左上角移动到圆弧中心位置
        text_rect.moveLeft(point_on_arc.x() - text_rect.width() / 2)
        text_rect.moveTop(point_on_arc.y() - text_rect.height() / 2)

        # 绘制文字
        painter.setFont(self.text_font)
        painter.drawText(text_rect, Qt.AlignCenter, text)

        self.textRect = text_rect  # 保存文字矩形

        # 恢复之前的状态
        painter.restore()

    def erase_text(self, painter):
        # 使用背景色覆盖文本矩形区域
        if self.text_rect:
            # 获取文本所在区域的背景色
            background_color = self.scene().backgroundBrush().color()  # 或者指定的背景色

            # 使用背景色填充文本矩形区域
            painter.fillRect(self.text_rect, background_color)
        self.update()
