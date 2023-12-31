/* 问题描述：
 * 求将正整数 n 无序拆分为最大数为 k 的拆分方案个数
 * 要求所有拆分方案不重复
 */

/* 输入：
 * 第一行两个整数，N，K，用空格隔开，正整数 n 与最大数 k。
5 5
 */

/* 输出：
将正整数5无序拆分成最大数为5的拆分方案个数为7
 */

#include <iostream>

using namespace std;

const int N = 1010;

int n, k;     // 正整数 n 与最大数 k
int f[N][N];  // 正整数 i 无序拆分为最大数为 j 的

int main()
{
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j)
        {
            if (i == 1 || j == 1)  // 只有一种划分，{1} || {1,1,....1,1,1}
            {
                f[i][j] = 1;
            }
            else if (j > i)  // 正整数小于最大数，等同于最大数为正整数的拆分方案个数
            {
                f[i][j] = f[i][i];
            }
            else if (i == j)  // 正整数等于最大数，根据划分中是否包含 j，分为两种情况
            {
                f[i][j] = f[i][j - 1] + 1;
            }
            else            // 正整数大于最大数，根据划分中是否包含 j，分为两种情况
            {
                f[i][j] = f[i][j - 1] + f[i - j][j];
            }
        }

    cout << "将正整数" << n << "无序拆分成最大数为" << k << "的拆分方案个数为" << f[n][k] << '\n';

    return 0;
}