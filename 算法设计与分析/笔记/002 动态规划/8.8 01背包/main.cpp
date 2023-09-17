/* 输入：
 * 第一行两个整数，N，V，用空格隔开，分别表示物品数量和背包容积。
 * 接下来有 N 行，每行两个整数 vi,wi，用空格隔开，分别表示第 i 件物品的体积和价值。
5 10
2 6
2 3
6 5
5 4
4 6
 */

/* 输出：
 * 选取的物品：1 2 5
 * 总价值：15
 */
#include <iostream>

using namespace std;

const int N = 1010;

int n, m;           // 物品数量、背包容积
int f[N][N];        // 前 i 个物品中选，背包容积为 j，最大价值
int w[N], v[N];     // 物品价值、物品体积
int num[N];         // 物品 i 是否被选取

/*
 * 功能：输出选择的物品
 */
void dispChoice()
{
    int k{ m };
    for (int i = n; i >= 1; --i)
    {
        if (f[i][k] == f[i - 1][k])
        {
            num[i] = 0;
        }
        else
        {
            num[i] = 1;
            k -= v[i];
        }
    }

    cout << "选取的物品：";
    for (int i = 1; i <= n; ++i)
    {
        if (num[i])
        {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
            {
                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            }

        }

    dispChoice();

    cout << "总价值：" << f[n][m] << '\n';

    return 0;
}
