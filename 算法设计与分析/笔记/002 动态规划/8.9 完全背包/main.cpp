/* 输入：
 * 第一行两个整数，N，V，用空格隔开，分别表示物品数量和背包容积。
 * 接下来有 N 行，每行两个整数 vi,wi，用空格隔开，分别表示第 i 件物品的体积和价值。
3 7
3 4
4 5
2 3
 */

/* 输出：
 * 选取的物品：
 * 物品3有2件
 * 物品2有0件
 * 物品1有1件
 * 总价值为：10
 */
#include <iostream>

using namespace std;

const int N = 1010;

int n, m;           // 物品数量、背包容积
int f[N][N];        // 前 i 个物品中选，背包容积为 j，最大价值
int w[N], v[N];     // 物品价值、物品体积
int num[N][N];      // f[i][j] 取最大值时物品 i 选取的个数

/*
 * 功能：输出选择的物品
 */
void dispChoice()
{
    int k{ m };
    cout << "选取的物品：\n";
    for (int i = n; i >= 1; --i)
    {
        cout << "物品" << i << "有" << num[i][k] << "件\n";
        k -= num[i][k] * v[i];
    }
}

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];


    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 0; k * v[i] <= j; ++k)  // 注：k 从 0 开始取
            {
                if (f[i][j] <= f[i - 1][j - k * v[i]] + k * w[i])
                {
                    f[i][j] = f[i - 1][j - k * v[i]] + k * w[i];
                    num[i][j] = k;
                }

            }


    dispChoice();
    cout << "总价值为：" << f[n][m] << '\n';

    return 0;

}