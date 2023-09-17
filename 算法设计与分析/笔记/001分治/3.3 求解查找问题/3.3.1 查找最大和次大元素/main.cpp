/* 问题描述：
对于给定的含有 n 个元素的无序序列，求这个序列中最大和次大的两个不同元素。
 */

/* 输入：
输入共两行，第一行包含整数 n 。
第二行包含 n 个整数，表示整个数列。
5
3 1 2 4 5
 */

/* 输出：
最大元素：5
次大元素：4
 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1010;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
int max1, max2;  // 最大元素、次大元素

void solve(int a[], int l, int r, int& max1, int& max2)
{
    if (l == r)
    {
        max1 = a[l];
        max2 = -INF;
    }
    else if (r - l == 1)
    {
        max1 = max(a[l], a[r]);
        max2 = min(a[l], a[r]);
    }
    else
    {
        int mid = l + r >> 1;
        int lmax1{}, lmax2{};
        int rmax1{}, rmax2{};
        solve(a, l, mid, lmax1, lmax2);
        solve(a, mid + 1, r, rmax1, rmax2);

        if (lmax1 > rmax1)
        {
            max1 = lmax1;
            max2 = max(lmax2, rmax1);
        }
        else
        {
            max1 = rmax1;
            max2 = max(lmax1, rmax2);
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    solve(a, 0, n - 1, max1, max2);
    cout << "最大元素：" << max1 << '\n';
    cout << "次大元素：" << max2 << '\n';

    return 0;
}