/* 问题描述：
 * 给定一个无序的整数序列，求其中最长递增子序列的长度
 */

/* 输入：
第一行包含两个整数 N。
第二行包含 N 个整数。
9
2 1 5 3 6 4 8 9 7
 */

/* 输出（不唯一）：
最大递增子序列：2 5 6 8 9
最长递增子序列的长度：5
 */
#include<iostream>
#include<algorithm>
#include<stack>

using namespace std;

const int N = 1010;

int n;
int a[N];
int f[N];    // 以 a[i] 结尾的最长递增子序列的长度
int pre[N];  // 以 a[i] 结尾的最长递增子序列的前驱结点的下标
int res{};   // 最长递增子序列的长度
int cur{};   // 最长递增子序列的最后一个结点的下标
stack<int>LIS;

/*
 * 功能：输出LIS
 */
void dispLIS()
{

    for (int i = 1; i <= res; ++i)
    {
        LIS.push(a[cur]);
        cur = pre[cur];
    }
    cout << "最大递增子序列：";
    for (int i = 1; i <= res; ++i)
    {
        cout << LIS.top() << ' ';
        LIS.pop();
    }
    cout << '\n';
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // 初始化
    for (int i = 1; i <= n; ++i)
    {
        f[i] = 1;
        pre[i] = i;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
        {
            if (a[i] > a[j] && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
                pre[i] = j;
            }
        }

    for (int i = 1; i <= n; ++i)
    {
        if (res <= f[i])
        {
            res = f[i];
            cur = i;
        }
    }

    dispLIS();
    cout << "最长递增子序列的长度：" << res << '\n';
}


