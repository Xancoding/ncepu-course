/* 问题描述：
 * 假设有一个需要使用某一资源的由 n 个活动组成的集合 S。该资源在任何时刻只能被一个活动所占用
 * 活动 i 有一个开始时间 b 和结束 e，其执行时间为 e - b，假设最早活动执行时间为 0.一旦某个活动开始执行，就不能被打断，直到其执行完毕。
 * 设计算法求一种最有活动安排方案，使得所有安排的活动个数最多
 */

/* 求解思路：
 * 该问题可以用贪心算法解决，其核心思想是每次选择结束时间最早的活动，以便为后续的活动留下更多的时间。
 */

/* 输入：
11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 15
 */

/* 输出：
选取的活动：
[1, 4][5, 7][8, 11][12, 15]
共4个活动
 */
#include <iostream>

using namespace std;

const int N = 1010;

int n;         // n 个活动
int cnt;       // 选取的兼容活动的个数
bool flag[N];  // 标记选择的活动

struct Action
{
    int st;    // 活动开始时间
    int ed;    // 活动结束时间
    bool operator<(const Action& s) const
    {
        return ed <= s.ed;
    }
};

int main()
{
    cout << "活动个数n：\n";
    cin >> n;

    Action action[n];
    cout << "活动 开始时间 结束时间（空格隔开）：\n";
    for (int i = 0; i < n; ++i) cin >> action[i].st >> action[i].ed;
    sort(action, action + n);  // 按活动结束时间递增排序

    int preEnd{ 0 };                        // 前一个兼容活动结束时间
    for (int i = 0; i < n; ++i)
    {
        if (action[i].st >= preEnd)
        {
            flag[i] = true;
            preEnd = action[i].ed;
        }
    }

    cout << "选取的活动：\n";
    for (int i = 0; i < n; ++i)
    {
        if (flag[i])
        {
            printf("[%d, %d]", action[i].st, action[i].ed);
            ++cnt;
        }
    }
    printf("\n共%d个活动\n", cnt);

    return 0;
}