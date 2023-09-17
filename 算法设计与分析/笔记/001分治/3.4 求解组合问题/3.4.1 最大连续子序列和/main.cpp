/* 问题描述：
 * 给定一个有 n 个整数的序列，求出其中最大连续子序列的和
 */

/* 输入：
输入共e二行，第一行包含整数 n。
第二行包含 n 个整数
6
-2 11 -4 13 -5 -2
 */

/* 输出：
最大子序列和为：20
 */
#include<iostream>
using namespace std;

typedef long long LL;

const int N = 1010;
const int INF = 0x3f3f3f3f;

int n;
int a[N];


// 求解跨越左右两边的最大子序列和
LL maxCrossSum(int a[], int l, int mid, int r)
{
    LL sum = 0, leftSum = -INF, rightSum = -INF;
    // 从中间位置向左求解最大子序列和
    for (int i = mid; i >= l; --i)
    {
        sum += a[i];
        leftSum = max(leftSum, sum);
    }
    sum = 0;
    // 从中间位置向右求解最大子序列和
    for (int i = mid + 1; i <= r; ++i)
    {
        sum += a[i];
        rightSum = max(rightSum, sum);
    }
    // 返回跨越左右两边的最大子序列和
    return leftSum + rightSum;
}

// 分治求解最大连续子序列和
LL maxSubSum(int a[], int l, int r)
{
    if (l == r) return a[l]; // 当序列长度为1时，直接返回该数值

    int mid = l + r >> 1; // 将序列分为两部分，求解中间位置
    LL leftMax = maxSubSum(a, l, mid); // 递归求解左半部分的最大连续子序列和
    LL rightMax = maxSubSum(a, mid + 1, r); // 递归求解右半部分的最大连续子序列和
    LL crossMax = maxCrossSum(a, l, mid, r); // 求解跨越左右两边的最大子序列和

    return max(leftMax, max(rightMax, crossMax)); // 返回三者中的最大值
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    cout << "最大连续子序列和：" << maxSubSum(a, 0, n - 1);
    return 0;
}
