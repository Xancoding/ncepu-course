def get_language(file_name: str) -> list:  # 从txt文件中获取文法产生式
    f = open(file_name, 'r')
    language = []
    for line in f:
        line = line.strip()
        if not line:
            continue
        if line == '\n':
            continue
        line = line.strip('\n')
        language.append(line)
    return language


def sort_by_key(d):
    return sorted(d.items(), key=lambda k: k[0])


class State(object):

    def __init__(self,
                 num: int,
                 len: int = 0) -> None:
        self.num = num  # 状态标号
        self.len = len  # 状态长度
        self.state_projects = []  # 状态所含的项目集
        self.is_final_state = False  # 是否为终态

    def add_project(self, project: str) -> list:  # 向状态中添加项目
        self.state_projects.append(project)
        if len(set(self.state_projects)) != len(self.state_projects):  # 判重
            self.state_projects.pop()
            return self.state_projects
        self.len += 1
        return self.state_projects


class Relation(object):

    def __init__(self, in_state: State, out_state: State,
                 character: str, rules: list) -> None:
        self.in_state = in_state
        self.out_state = out_state
        self.character = character
        self.rules = rules


class LR0(object):

    def __init__(self,
                 language: list,
                 state_num: int,
                 relation_num: int) -> None:
        self.language = language  # 文法产生式，由txt文件转化而来
        self.state_num = state_num  # 状态数量
        self.relation_num = relation_num  # 转化边的数量
        self.language_extended = []  # 拓广文法
        self.projects = []  # 由拓广文法生成的项目
        self.projects_1d = []  # 将projects展为一维列表
        self.states_list = []  # 状态列表
        self.relation_list = []  # 转化边列表
        self.state_exist_or_not = {}  # 用于识别每个状态是否存在，元素格式：状态编号：项目集
        self.state_need2generate_relation = []  # 存储“已经求完闭包但是没有求后续状态的状态”的堆栈
        self.characters_upper = []  # 非终结符
        self.characters_lower = []  # 终结符
        self.action_goto_table = []  # action-goto表

    def extend_language(self) -> list:  # 拓广文法，加一个$->S
        init = '$->' + self.language[0][0]
        self.language_extended.append(init)
        self.language_extended += self.language
        return self.language_extended

    def generate_projects(self) -> list:  # 生成项目
        for line in self.language_extended:
            if line[-1] == '@':  # 处理空产生式， S->@只生成S->.
                temp = []
                temp.append(line[0] + '->.')
                self.projects.append(temp)
            else:  # 处理非空产生式， S->aS 生成 S->.aS S->a.S S->aS.
                l_splited = line.split('->')
                temp = []
                for i in range(len(l_splited[1]) + 1):
                    str_list = list(l_splited[1])
                    str_list.insert(i, '.')
                    str = ''.join(str_list)
                    tmp = l_splited[0] + '->' + str
                    temp.append(tmp)
                self.projects.append(temp)
        self.projects_1d = [i for item in self.projects for i in item]
        return self.projects

    # TODO 非lr0
    # def generate_state_closure(self, state_i: State) -> State:  # 生成每个状态的闭包（输入可以有移进规约——冲突）
    #     for p in state_i.state_projects:
    #         right_char = p.split('->')[1]
    #         char_after_point = right_char.split('.')[1]
    #         if char_after_point == "":  # 终态
    #             state_i.is_final_state = True
    #         else:
    #             first_char_after_point = char_after_point[0]
    #             for i in range(len(self.projects)):
    #                 left_char = self.projects[i][0].split('->')[0]
    #                 if left_char == first_char_after_point:
    #                     state_i.add_project(self.projects[i][0])
    #     return state_i

    # TODO lr0
    def generate_state_closure(self, state_i: State) -> State:  # 生成每个状态的闭包
        for p in state_i.state_projects:
            right_char = p.split('->')[1]  # 获取产生式右部
            char_after_point = right_char.split('.')[1]  # 获取点后面的字符串
            if char_after_point == "":  # 终态
                state_i.is_final_state = True
                return state_i
            first_char_after_point = char_after_point[0]  # 点的后跟字符
            for i in range(len(self.projects)):  # 左部和点的后跟字符相同的都加进去
                left_char = self.projects[i][0].split('->')[0]
                if left_char == first_char_after_point:
                    state_i.add_project(self.projects[i][0])
        return state_i

    def generate_relation_and_following_states(self, in_state: State) -> None:  # 生成边和跟随的状态集
        character_set = {}  # 字符：项目
        for p in in_state.state_projects:  # 生成character_set
            str_after_point = p.split('->')[1].split('.')[1]
            if str_after_point != "":  # 如果不是S->aA.这种
                relation_char = str_after_point[0]
                find_project_index = self.projects_1d.index(str(p)) + 1
                project = self.projects_1d[find_project_index]
                if relation_char in character_set:  # 当边上的字符已经存在，就只添加项目就行
                    character_set[relation_char].add(project)
                else:  # 边上的字符还没创建的时候，就创建一个新状态
                    character_set[relation_char] = {project}
        for char in character_set:
            project_set = character_set[char]
            if char.isupper():
                self.characters_upper.append(char)
            else:
                self.characters_lower.append(char)
            if project_set in list(self.state_exist_or_not.values()):  # 已经存在的状态（只需要生成新关系）
                out_state_index = list(self.state_exist_or_not.values()).index(project_set)
                out_state = self.states_list[out_state_index]
                new_relation = Relation(
                    in_state=in_state,
                    out_state=out_state,
                    character=char,
                    rules=list(project_set))
                self.relation_list.append(new_relation)
                self.relation_num += 1
            else:  # 不存在的状态。同时生成关系和状态
                new_state = State(self.state_num)  # 生成新状态
                for project in project_set:
                    new_state.add_project(project)
                new_state = self.generate_state_closure(new_state)
                self.states_list.append(new_state)

                # TODO lr0
                if not new_state.is_final_state:
                    self.state_need2generate_relation.append(new_state)
                # TODO 非lr0
                # self.state_need2generate_relation.append(new_state)

                self.state_exist_or_not[self.state_num] = project_set
                self.state_num += 1
                new_relation = Relation(  # 生成新关系
                    in_state=in_state,
                    out_state=new_state,
                    character=char,
                    rules=list(project_set))
                self.relation_list.append(new_relation)
                self.relation_num += 1

    def generate_dfa(self):  # 添加每个状态的初始项目
        # 生成状态I0
        i0 = State(num=0)
        project = self.projects[0][0]
        i0.add_project(project=project)  # 为I0添加初始项目
        i0 = self.generate_state_closure(i0)  # 生成I0的闭包
        self.states_list.append(i0)
        project_set = {project}
        self.state_exist_or_not[0] = project_set
        self.state_num += 1
        self.state_need2generate_relation.append(i0)  # 把I0放入堆栈
        # 生成其他的状态
        while len(self.state_need2generate_relation) != 0:
            self.generate_relation_and_following_states(self.state_need2generate_relation[0])
            self.state_need2generate_relation.pop(0)
        return self.states_list, self.relation_list

    def create_action_goto_table(self):
        self.characters_lower = list(set(self.characters_lower))
        self.characters_lower.append("#")
        self.characters_upper = list(set(self.characters_upper))
        row_title = [''] + self.characters_lower + self.characters_upper
        self.action_goto_table.append(row_title)
        idx = 0
        for state in self.states_list:
            row_temp = [str(idx)]
            for i in range(len(row_title) - 1):
                row_temp.append('')

            if state.is_final_state:  # 终态
                if state.state_projects[0][0] == '$':  # 接受
                    row_temp[row_title.index('#')] = "acc"
                else:  # 规约
                    for i in range(1, len(self.characters_lower) + 1):
                        row_temp[i] = "r" + str(self.language_extended.index(state.state_projects[0][0:-1]))
                self.action_goto_table.append(row_temp)
            else:  # 非终态
                for i in range(1, len(self.characters_lower) + 1):  # action
                    for relation in self.relation_list:
                        if relation.character == row_title[i] and relation.in_state.num == idx:
                            row_temp[i] = "S" + str(relation.out_state.num)
                for i in range(len(self.characters_lower) + 1, len(row_title)):  # goto
                    for relation in self.relation_list:
                        if relation.in_state.num == idx and relation.character == row_title[i]:
                            row_temp[i] = str(relation.out_state.num)
                self.action_goto_table.append(row_temp)
            idx += 1
        return self.action_goto_table

    def str_analyze(self, input_str):
        analyticable = True
        analyze_table = []
        table_head = ['step', 'state stack', 'char stack', 'input str', 'ACTION', 'GOTO']
        analyze_table.append(table_head)
        step = 1
        state_stack = [0]
        char_stack = "#"
        input_str = input_str + "#"
        while True:
            try:
                check_action_table = self.action_goto_table[int(state_stack[-1]) + 1][
                    self.action_goto_table[0].index(input_str[0])]
            except:
                analyze_table.append(["error", "error", "error", "error", "error", "error"])
                analyticable = False
                break
            if check_action_table == "":
                analyze_table.append(["error", "error", "error", "error", "error", "error"])
                analyticable = False
                break
            elif check_action_table[0] == "S":  # Sj
                ss = ""
                for i in state_stack:
                    if i > 9:
                        ss += "(" + str(i) + ")"
                    else:
                        ss += str(i)
                table_row = [str(step), ss, char_stack, input_str, check_action_table, ""]
                state_stack.append(int(check_action_table[1:]))
                char_stack += input_str[0]
                input_str = input_str[1:]
                step += 1
                analyze_table.append(table_row)
            elif check_action_table[0] == "r":  # rj
                ss = ""
                for i in state_stack:
                    if i > 9:
                        ss += "(" + str(i) + ")"
                    else:
                        ss += str(i)
                rule = self.language_extended[int(check_action_table[1:])]
                check_goto_table = self.action_goto_table[state_stack[-1 - (len(rule) - 3)] + 1][
                    self.action_goto_table[0].index(rule[0])]
                table_row = [str(step), ss, char_stack, input_str, check_action_table, str(check_goto_table)]
                state_stack = state_stack[0:-len(rule) + 3]
                state_stack.append(int(check_goto_table))
                char_stack = char_stack[0:-len(rule) + 3]
                char_stack += rule[0]
                step += 1
                analyze_table.append(table_row)
            elif check_action_table == "acc":
                table_row = [str(step), "01", char_stack, input_str, check_action_table, ""]
                analyze_table.append(table_row)
                break
        return analyticable, analyze_table


if __name__ == '__main__':
    file_name = "test_input/test_data0.txt"
    language = get_language(file_name=file_name)

    lr0 = LR0(language=language, state_num=0, relation_num=0)
    language_extended = lr0.extend_language()
    projects = lr0.generate_projects()

    state_list, relation_list = lr0.generate_dfa()
    ag_table = lr0.create_action_goto_table()
    analyticable, at = lr0.str_analyze("b")
