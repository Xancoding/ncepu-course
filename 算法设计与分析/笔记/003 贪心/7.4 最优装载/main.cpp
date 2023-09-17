/* 问题描述：
 * 有 n 个集装箱要装上一艘载重量为 W 的轮船，其中集装箱 i 的重量为 wi。
 * 不考虑集装箱的体积限制，现要选出尽可能多的集装箱装上轮船，使它们重量之和不超过 W。
 */

/* 求解思路：
 * 优先选取重量轻的集装箱装船
 */

/* 输入：
5 10
5 2 6 4 3
 */

/* 输出：
最优方案：
重量为 2 的集装箱
重量为 3 的集装箱
重量为 4 的集装箱
总重量=9
 */

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;      // 集装箱总数量、轮船载重量
int w[N];      // 各集装箱重量
int num[N];    // 集装箱是否被选取

int main()
{
    cout << "集装箱总数量、轮船载重量：\n";
    cin >> n >> m;

    cout << "各集装箱的重量：\n";
    for (int i = 0; i < n; ++i) cin >> w[i];
    sort(w, w + n);

    int res{ 0 };  // 装载货物重量总和
    for (int i = 0; i < n && m >= w[i]; ++i)
    {
        num[i] = 1;
        m -= w[i];
        res += w[i];
    }

    cout << "最优方案：\n";
    for (int i = 0; i < n; ++i)
    {
        if (num[i])
        {
            printf("重量为 %d 的集装箱\n", w[i]);
        }
    }

    cout << "总重量=" << res << '\n';

    return 0;
}