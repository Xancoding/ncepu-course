from src.dlg.matrix_dlg import MatrixDlg
from src.abstract_automata import AbstractAutomata, Func
from src.elements.edge import Edge
from PyQt5.QtCore import Qt, QPointF
from PyQt5.QtGui import QPainter
from PyQt5.QtWidgets import QGraphicsView, QGraphicsScene, QFileDialog
from src.dlg.add_edge_dlg import AddEdgeDlg
from src.dlg.add_node_dlg import AddNodeDlg
from src.elements.node import Node


class GraphWidget(QGraphicsView):
    def __init__(self, parent=None):
        super(GraphWidget, self).__init__(parent)
        # 初始化场景和视图属性
        self.scene = QGraphicsScene(self)  # 创建图形场景
        self.setScene(self.scene)  # 设置场景
        self.setSceneRect(0, 0, 400, 400)  # 设置场景大小
        self.setRenderHint(QPainter.Antialiasing)  # 渲染属性

        self.nodes = []  # 节点列表
        self.edges = []  # 边列表

        self.mode = "MOVE"  # 设置默认模式为“移动”

        self.node_to_move = None  # "MOVE"模式下选定的节点

    def set_mode(self, new_mode):
        """设置模式"""
        self.mode = new_mode

    def check_if_node_clicked(self, event):
        """检查点击是否在节点上"""
        scene_pos = self.mapToScene(event.pos())
        items = self.scene.items(scene_pos)
        for item in items:
            if isinstance(item, Node) and item.shape().contains(item.mapFromScene(scene_pos)):
                return item
        return None

    def check_if_edge_clicked(self, event):
        """检查点击是否在边上"""
        scene_pos = self.mapToScene(event.pos())
        items = self.scene.items(scene_pos)
        for item in items:
            if isinstance(item, Edge) and item.shape().contains(item.mapFromScene(scene_pos)):
                return item
        return None

    def check_if_node_exist(self, node_name):
        """检查节点是否存在"""
        return any(node.m_nodeName == node_name for node in self.nodes)

    def check_if_edge_exist(self, source_node, dest_node):
        """检查边是否存在"""
        return any(edge.source.m_nodeName == source_node and edge.dest.m_nodeName == dest_node for edge in self.edges)

    def get_node_by_name(self, node_name):
        """根据名称获取节点"""
        return next((node for node in self.nodes if node.m_nodeName == node_name), None)

    def mousePressEvent(self, event):
        """
        鼠标点击事件。

        根据当前模式处理不同的鼠标点击事件：
        - 如果模式为“ADD_NODE”，并且用户使用左键单击，触发添加节点操作。
        - 如果模式为“MOVE”，并且用户使用左键单击节点，记录选中节点以进行移动操作。
        - 如果模式为“ADD_EDGE”，并且用户在空白区域使用左键单击，弹出添加边的对话框。
        - 如果模式为"DELETE"，并且用户使用左键单击节点，删除该节点；如果用户使用左键单击边，删除该边。

        参数:
            event (QMouseEvent): 鼠标事件对象。
        """
        if self.mode == "ADD_NODE":
            self.handle_add_node(event)
        elif self.mode == "MOVE":
            self.handle_move(event)
        elif self.mode == "ADD_EDGE":
            self.handle_add_edge(event)
        elif self.mode == "DELETE":
            self.handle_delete(event)

    def handle_add_node(self, event):
        if event.button() == Qt.LeftButton:
            pos = event.pos()
            scene_pos = self.mapToScene(pos)
            dialog = AddNodeDlg(self, scene_pos.x(), scene_pos.y())
            dialog.exec_()

    def handle_move(self, event):
        if event.button() == Qt.LeftButton:
            node_item = self.check_if_node_clicked(event)
            if node_item:
                self.node_to_move = node_item

    def handle_add_edge(self, event):
        if event.button() == Qt.LeftButton:
            node_item = self.check_if_node_clicked(event)
            if node_item is None:
                dialog = AddEdgeDlg(self)
                dialog.exec_()

    def handle_delete(self, event):
        if event.button() == Qt.LeftButton:
            node_item = self.check_if_node_clicked(event)
            if node_item:
                self.remove_node(node_item)

            edge_item = self.check_if_edge_clicked(event)
            if edge_item:
                self.remove_edge(edge_item)

    def remove_node(self, node_item):
        self.scene.removeItem(node_item)
        self.nodes.remove(node_item)
        for edge in self.edges[:]:
            if edge.source.m_nodeName == node_item.m_nodeName or edge.dest.m_nodeName == node_item.m_nodeName:
                self.scene.removeItem(edge)
                self.edges.remove(edge)
        self.scene.update()

    def remove_edge(self, edge_item):
        self.scene.removeItem(edge_item)
        self.edges.remove(edge_item)
        self.scene.update()

    def add_edge(self, source_node, dest_node, input_list, re_input_list):
        """添加边到图形场景中"""
        if self.check_if_edge_exist(source_node, dest_node) is False:
            # 边不存在，添加边
            edge = Edge(self, source_node, dest_node, input_list, re_input_list)
            self.scene.addItem(edge)
            self.edges.append(edge)
        else:
            # 边已存在，更新边的输入列表
            edge = next((edge for edge in self.edges if edge.source.m_nodeName == source_node
                         and edge.dest.m_nodeName == dest_node), None)
            edge.input_list.extend(input_list)
            edge.re_input_list.extend(re_input_list)
            # 去除列表中重复的元素并排序
            edge.input_list = sorted(list(set(edge.input_list)))
            edge.re_input_list = sorted(list(set(edge.re_input_list)))

            painter = QPainter(self)  # 创建一个 QPainter 对象
            edge.erase_text(painter)  # 更新边上的文字

    def add_node(self, name, node_cas, x, y):
        """添加点到图形场景中"""
        node = Node(self, name, node_cas)
        self.scene.addItem(node)
        node.setPos(QPointF(x, y))
        self.nodes.append(node)

    def mouseMoveEvent(self, event):
        """鼠标移动事件"""
        if not self.mode == "MOVE" or self.node_to_move is None:
            return  # 如果模式不是“移动”，或者没有选定节点，不进行移动操作

        # 移动节点
        scene_pos = self.mapToScene(event.pos())
        self.node_to_move.setPos(scene_pos)

        # 获取移动的节点名称
        moved_node_name = self.node_to_move.m_nodeName

        # 当节点移动时，更新连接到该节点的所有边的位置
        for edge in self.edges:
            # 调用边的更新方法
            if edge.source.m_nodeName == moved_node_name or edge.dest.m_nodeName == moved_node_name:
                self.scene.removeItem(edge)
                edge.source_point = QPointF(*edge.source.get_center())
                edge.dest_point = QPointF(*edge.dest.get_center())
                self.scene.addItem(edge)
                self.scene.update()

    def mouseReleaseEvent(self, event):
        """鼠标释放事件"""
        if self.mode == "MOVE" and self.node_to_move:
            self.node_to_move = None

    def from_file(self):
        """从文件读取"""
        options = QFileDialog.Options()
        file_name, _ = QFileDialog.getOpenFileName(self, "打开图形文件", "files/",
                                                   "图形文件 (*.graph);;所有文件 (*)", options=options)
        if file_name:
            # 清空图形部件
            self.clear()
            try:
                with open(file_name, 'r', encoding='utf-8') as file:
                    # 读取节点数
                    node_num = int(file.readline())
                    # 读取每个节点的信息
                    for _ in range(node_num):
                        node_name, node_state, x, y = file.readline().split()
                        self.add_node(node_name, int(node_state), float(x), float(y))

                    # 读取边数
                    edge_num = int(file.readline())
                    # 读取每条边的信息
                    for _ in range(edge_num):
                        edge_info = file.readline().split()
                        source_node = edge_info[0]
                        dest_node = edge_info[1]
                        input_data = edge_info[2:]

                        # 将输入和逆向输入从列表中分割
                        input_list = []
                        re_input_list = []
                        for data in input_data:
                            if '#' in data:
                                re_input_list = data.split('#')[1:]
                            else:
                                input_list.append(data)

                        # 添加边到图形场景
                        self.add_edge(source_node, dest_node, input_list, re_input_list)

                    print("成功加载文件:", file_name)
            except Exception as e:
                print("加载文件出错:", str(e))
        else:
            print("未选择文件")

    def to_file(self):
        """输出到文件"""
        options = QFileDialog.Options()
        file_name, _ = QFileDialog.getSaveFileName(self, "保存图形",
                                                   "files/",
                                                   "图形文件 (*.graph);;所有文件 (*)", options=options)

        if file_name:
            try:
                with open(file_name, 'w') as file:
                    # 写入节点数
                    file.write(f"{len(self.nodes)}\n")
                    for node in self.nodes:
                        # 写入每个节点的信息
                        file.write(f"{node.m_nodeName} {node.m_nodeState} {node.pos().x()} {node.pos().y()}\n")

                    # 写入边数
                    file.write(f"{len(self.edges)}\n")
                    for edge in self.edges:
                        # 写入每条边的信息
                        file.write(f"{edge.source.m_nodeName} {edge.dest.m_nodeName} "
                                   f"{' '.join(map(str, edge.input_list))} "
                                   f"#{' '.join(map(str, edge.re_input_list))}\n")

                # 提示保存成功
                print("图形保存成功。")
            except Exception as e:
                # 如果保存出现异常，提示保存失败
                print(f"保存图形失败: {str(e)}")

    def to_matrix(self):
        """输出到邻接矩阵"""
        state_set = [node.m_nodeName for node in self.nodes]  # 状态集合列表
        input_list = []
        for edge in self.edges:
            input_list.extend(edge.input_list)
            input_list.extend(edge.re_input_list)
        input_list = sorted(list(set(input_list)))
        input_list = list(filter(None, input_list))  # 去除列表中的空元素
        init_state = [node.m_nodeName for node in self.nodes if node.m_nodeState & 1]
        final_state_set = [node.m_nodeName for node in self.nodes if node.m_nodeState & 2]

        # 创建抽象自动机对象
        absract_automata = AbstractAutomata()
        absract_automata.sl_state_set = state_set
        absract_automata.sl_input_list = input_list
        absract_automata.s_init_state = init_state
        absract_automata.sl_final_state_set = final_state_set

        # 从图形部件中获取边的信息
        for edge in self.edges:
            # 将边的信息添加到抽象自动机对象中
            for input_ in edge.input_list:
                absract_automata.func_list.append(Func(edge.source.m_nodeName, edge.dest.m_nodeName, input_))
            for re_input in edge.re_input_list:
                absract_automata.func_list.append(Func(edge.dest.m_nodeName, edge.source.m_nodeName, re_input))

        dialog = MatrixDlg(self)
        dialog.setup_matrix(absract_automata)
        dialog.exec_()

    def from_matrix(self):
        """从邻接矩阵生成图"""
        # 从对话框获取邻接矩阵
        dialog = MatrixDlg(self)
        dialog.exec_()

    def clear(self):
        """清空图形"""
        self.scene.clear()
        self.nodes.clear()
        self.edges.clear()
        self.scene.update()

