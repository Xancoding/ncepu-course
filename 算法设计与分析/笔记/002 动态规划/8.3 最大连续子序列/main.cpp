/* 问题描述：
给定一个有 n 个整数的序列，求出其中最大连续子序列的和
 */
/* 输入：
 * 第一行两个整数，N，表示序列长度。
 * 接下来有 1 行，N 个整数。
6
-2 11 -4 13 -5 -2
 */

/* 输出：
所选子序列：11 -4 13
最大连续子序列和为：20
 */
#include <iostream>

using namespace std;

const int N = 1010;

int n;         // 序列长度
int a[N];
int f[N];      // 以 a[i] 为结尾的最大连续子序列和
int resIndex;  // 最大子序列和的最后一个整数的下标
/*
 * 功能：输出选择的子序列
 */
void dispChoice()
{
    // 找到最大连续子序列

    for (int i = 1; i <= n; ++i)
    {
        if (f[i] >= f[resIndex])
        {
            resIndex = i;
        }
    }

    // 找到前一个小于等于 0 者
    // 若 f[i] <= 0，则f[i + 1] - a[i]
    // 即 a[i] 不在最大连续子序列中
    int k{ 1 };
    for (int i = resIndex; i >= 1; --i)
    {
        if (f[i] <= 0)
        {
            k = i;
            break;
        }
    }

    cout << "所选子序列：";
    for (int i = k + 1; i <= resIndex; ++i)
        cout << a[i] << ' ';

    cout << '\n';
}

int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> a[i];


    for (int i = 1; i <= n; ++i)
    {
        f[i] = max(a[i], f[i - 1] + a[i]);
    }

    dispChoice();

    cout << "最大连续子序列和为：" << f[resIndex] << '\n';

    return 0;
}
