/* 安全性算法：
 * 若安全，输出所有安全序列
 * 1. 初始化数据
 * 2. 查找满足一下两点的数据
 *      1. Finish = false
 *      2. Need <= Work
 * 若不存在，跳至第 4 步
 * 3. 当 Work = Work + Allocation，Finish = true 时，跳至第 2 布
 * 4. 若所有的 Finish = true，那么系统处于安全状态
 */
/* 资源请求算法：
 * 1. Request <= Need，跳至第 2 步。否则，产生错误条件
 * 2. Request <= Aviable，跳至第 3 步。否则，产生错误条件
 * 3. 分配资源，判断新状态是否安全
 */

/* 输入(不安全)：
进程数和资源种类数:
2 2
可用资源向量:
0 1
分配矩阵：
0 0
0 0
最大需求矩阵：
1 3
1 3
请求资源的进程编号：
2
请求向量：
0 1
 */

/* 输入(安全)：
进程数和资源种类数:
5 4
可用资源矩阵:
1 5 2 0
分配矩阵：
0 0 1 2
1 0 0 0
1 3 5 4
0 6 3 2
0 0 1 4
最大需求矩阵：
0 0 1 2
1 7 5 0
2 3 5 6
0 6 5 2
0 6 5 6
请求资源的进程编号：
2
请求向量：
0 4 2 0
 */
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Process {
public:
    int id{};  // 进程编号
    vector<int> allocation;  // 进程已分配的资源数
    vector<int> max;  // 进程最大需求的资源数
    vector<int> need;  // 进程还需要的资源数
    bool finish{};  // 进程是否完成
};

class System {
public:
    int n{};  // 进程数
    int m{};  // 资源种类数
    int number{};           // 请求资源的进程编号
    vector<int> request;    // 某个进程请求的资源数
    vector<int> available;  // 系统可用的资源数
    vector<Process> processes;  // 进程列表
    vector<int> work;  // 工作向量
    vector<int> work_tmp;  // 暂存工作向量
    vector<int> safe_sequence;  // 安全序列
    vector<vector<int>> all_safe_sequences;  // 所有安全序列

    // 打印初始化后的数据
    void print_init()
    {
        for (int i = 0; i < n; ++i)
        {
            Process p = processes[i];

            cout << '\n' << "进程" << p.id << "已分配的资源数：";
            for (int j = 0; j < m; ++j)
            {
                cout << p.allocation[j] << ' ';
            }

            cout << '\n' << "进程" << p.id << "最大需求的资源数：";
            for (int j = 0; j < m; ++j)
            {
                cout << p.max[j] << ' ';
            }

            cout << '\n' << "进程" << p.id << "需要的资源数：";
            for (int j = 0; j < m; ++j)
            {
                cout << p.need[j] << ' ';
            }
            cout << '\n';
        }
    }

    // 初始化数据
    void init() {
        cout << "Number of processes && Types of resources:" << endl;
        cin >> n >> m;
        cout << "Available resource vector:" << endl;
        for (int i = 0; i < m; i++) {
            int num;
            cin >> num;
            available.push_back(num);
        }

        cout << "Allocation matrix:\n";
        for (int i = 0; i < n; ++i) {
            auto* p = new Process;
            p->id = i + 1;
            for (int j = 0; j < m; ++j) {
                int num;
                cin >> num;
                p->allocation.push_back(num);
            }
            p->finish = false;
            processes.push_back(*p);
        }

        cout << "Max matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int num;
                cin >> num;
                processes[i].max.push_back(num);

                assert(num - processes[i].allocation[j] >= 0 && "Need < 0!!!");
                processes[i].need.push_back(num - processes[i].allocation[j]);  // 计算还需要的资源数
            }
        }

        work = available;

//        print_init();
    }

    // 初始化请求
    void init_request()
    {
        cout << "Request process number:\n";
        cin >> number;
        cout << "Request resource vector:\n";
        for (int i = 0; i < m; ++i)
        {
            int num;
            cin >> num;
            request.push_back(num);
        }

    }

    // 检查进程是否满足条件
    bool check(Process &p) {
        for (int i = 0; i < m; i++) {
            if (p.need[i] > work[i]) {
                return false;
            }
        }
        return true;
    }

    // 更新工作向量
    void update_work(Process &p) {
        for (int i = 0; i < m; i++) {
            work[i] += p.allocation[i];
        }
    }

    // 回退工作向量
    void remove_work(Process &p) {
        for (int i = 0; i < m; i++) {
            work[i] -= p.allocation[i];
        }
    }

    // 更新资源请求分配
    void update_resource(Process &p)
    {
        for (int i = 0; i < m; ++i)
        {
            available[i] -= request[i];
            p.allocation[i] += request[i];
            p.need[i] -= request[i];
        }
        work_tmp = work;
        work = available;
    }

    // 回退资源请求分配
    void remove_resource(Process &p)
    {
        for (int i = 0; i < m; ++i)
        {
            available[i] += request[i];
            p.allocation[i] -= request[i];
            p.need[i] += request[i];
        }
        work = work_tmp;
    }

    // 查找安全序列
    void find_safe_sequence(int count) {
        for (int i = 0; i < n; i++) {
            Process &p = processes[i];
            if (!p.finish && check(p)) {
                p.finish = true;
                safe_sequence.push_back(p.id);
                update_work(p);
                if (count == n - 1) {
                    all_safe_sequences.push_back(safe_sequence);
                } else {
                    find_safe_sequence(count + 1);
                }
                p.finish = false;
                safe_sequence.pop_back();
                remove_work(p);
            }
        }
    }

    void print_all_safe_sequences() {
        if (all_safe_sequences.empty())
        {
            cout << "The system status is unsafe!!!\n";
            return;
        }

        cout << "Total safe sequences：" << all_safe_sequences.size() << '\n';
        cout << "All safe sequences:" << endl;
        for (auto seq : all_safe_sequences) {
            cout << "[" << seq[0];
            for (int j = 1; j < seq.size(); j++) {
                cout << ", " << seq[j];
            }
            cout << "]" << endl;
        }
    }

    void resource_request()
    {
        Process &p = processes[number - 1];
        for (int i = 0; i < m; ++i)
        {
            assert(request[i] <= p.need[i] && "Request > Need!!!");
            assert(request[i] <= available[i] && "Request > Avaiable, No resources available!!!");
        }

        update_resource(p);
        all_safe_sequences.clear();  // 清空所有的安全序列
        find_safe_sequence(0);
        int length{ static_cast<int>(all_safe_sequences.size()) };
        if (length > 0)
        {
            cout << "Resources can be allocated immediately\n";
        }
        else
        {
            cout << "Resources can't' be allocated immediately!!!\n";
        }
        remove_resource(p);
    }
};

int main() {
    System system;
    system.init();
    system.find_safe_sequence(0);
    system.print_all_safe_sequences();

    system.init_request();
    system.resource_request();
    system.print_all_safe_sequences();
    return 0;
}