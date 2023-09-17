/* 问题描述：
 * 给定高度为 n 的一个整数三角形，找出从顶部到底部的最小路径和
 * 注意从每个整数出发只能向下移动到相邻的整数
 * 首先输入 n，接下来的 1~n 行，第 i 行输入 i 个整数
 * 输出分为两行，第 1 行为最小路径，第 2 行为最小路径和
 */

/* 输入：
4
2
3 4
6 5 7
8 3 9 2
 */

/* 输出：
路径是：2 3 5 3
最小路径和为：13
 */
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

const int N = 510;
const int INF = 1e9;

int n;
int a[N][N];
int f[N][N];     // 高度为 i，路径底部为 a[i][j] 的最小路径和
int pre[N][N];   // 高度为 i，路径底部为 a[i][j] 的最小路径的前驱结点下标
int res{ INF };  // 最小路径和
int cur{};       // 底部结点下标

/*
 * 功能：逆序输出最小路径
 */
void dispPath()
{
    cout << "路径是：";

    stack<int>path{};
    for (int i = n; i >= 1; --i)
    {
        path.push(a[i][cur]);
        cur = pre[i][cur];
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << path.top() << ' ';
        path.pop();
    }
    cout << '\n';
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            cin >> a[i][j];

    memset(f, 0x3f ,sizeof(f));

    f[1][1] = a[1][1];
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
        {
            if (f[i - 1][j] <= f[i - 1][j - 1])
            {
                f[i][j] = f[i - 1][j] + a[i][j];
                pre[i][j] = j;
            }
            else
            {
                f[i][j] = f[i - 1][j - 1] + a[i][j];
                pre[i][j] = j - 1;
            }
        }

    // 找到最小路径
    for (int i = 1; i <= n; ++i)
    {
        if (res >= f[n][i])
        {
            res = f[n][i];
            cur = i;
        }
    }

    dispPath();
    cout << "最小路径和为：" << res << '\n';

    return 0;
}
