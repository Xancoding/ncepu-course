class Func:
    def __init__(self, from_state, to_state, input_symbol):
        """
        转换函数对象的构造函数。

        参数：
        - from_state：转换的起始状态
        - to_state：转换的目标状态
        - input_symbol：转换所用的输入符号，单个符号
        """
        self.from_state = from_state  # 转换的起始状态
        self.to_state = to_state  # 转换的目标状态
        self.input_symbol = input_symbol  # 转换所用的输入符号


class AbstractAutomata:
    def __init__(self):
        """
        抽象 自动机 类的构造函数。
        初始化各种成员变量。
        """
        self.sl_state_set = []  # 状态集
        self.sl_input_list = []  # 输入符号表
        self.s_init_state = []  # 初态
        self.sl_final_state_set = []  # 终态集
        self.func_list = []  # 转换函数列表

    def clear(self):
        """
        清空所有存储的状态和转换函数。
        """
        self.sl_state_set.clear()  # 状态集
        self.sl_input_list.clear()  # 输入符号表
        self.s_init_state.clear()  # 初态
        self.sl_final_state_set.clear()  # 终态集
        self.func_list.clear()  # 转换函数列表

    def add_state_set(self, state):
        """
        向状态集中添加状态。

        参数：
        - state：要添加的状态

        返回：
        - True：如果成功添加
        - False：如果状态已存在于集合中
        """
        if state not in self.sl_state_set:
            self.sl_state_set.append(state)
            return True
        return False

    def add_init_state(self, state):
        """
        向初态集中添加状态。

        参数：
        - state：要添加的初态

        返回：
        - True：如果成功添加
        - False：如果初态已存在于集合中
        """
        if state not in self.s_init_state:
            self.s_init_state.append(state)
            return True
        return False

    def add_final_state(self, state):
        """
        向终态集中添加状态。

        参数：
        - state：要添加的终态

        返回：
        - True：如果成功添加
        - False：如果终态已存在于集合中
        """
        if state not in self.sl_final_state_set:
            self.sl_final_state_set.append(state)
            return True
        return False

    def add_func(self, from_state, to_state, input_symbol):
        """
        向转换函数列表中添加新的转换函数。

        参数：
        - from_state：转换的起始状态
        - to_state：转换的目标状态
        - input_symbol：转换所用的输入符号
        """
        func = Func(from_state, to_state, input_symbol)
        self.func_list.append(func)