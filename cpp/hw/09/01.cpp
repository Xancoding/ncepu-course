#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 初始化队列
    vector<int> queue = {1, 2, 3};

    // 模拟顾客加入队列
    cout << "初始队列：" << endl;
    for (int i : queue) {
        cout << i << " ";
    }
    cout << endl;

    queue.push_back(4);
    queue.push_back(5);
    cout << "顾客加入后：" << endl;
    for (int i : queue) {
        cout << i << " ";
    }
    cout << endl;

    // 模拟顾客放弃排队
    cout << "第二位顾客放弃排队：" << endl;
    queue.erase(queue.begin() + 1);
    for (int i : queue) {
        cout << i << " ";
    }
    cout << endl;

    // 模拟队列增长
    for (int i = 6; i <= 11; ++i) {
        queue.push_back(i);
    }
    cout << "队列增长后：" << endl;
    for (int i : queue) {
        cout << i << " ";
    }
    cout << endl;

    // 模拟开启新通道并转移顾客
    cout << "开启新通道并转移偶数位顾客：" << endl;
    vector<int> queue2;
    for (int i = 0; i < queue.size(); ++i) {
        if (i % 2 == 1) {
            queue2.push_back(queue[i]);
        }
    }
    for (int i : queue) {
        cout << i << " ";
    }
    cout << endl;
    cout << "新通道：" << endl;
    for (int i : queue2) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
