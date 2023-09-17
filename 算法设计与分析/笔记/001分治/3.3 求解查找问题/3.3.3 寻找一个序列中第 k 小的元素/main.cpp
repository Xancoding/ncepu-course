/* 问题描述：
 * 给定一个长度为 n 的整数数列，请用快速选择算法求出数列从小到大排序后的第 k 个数
 * 时间复杂度分析：
 * T(n) = T(n / 2) + O(n)
 * --> T(n) = O(n)
 */

/* 输入：
输入共两行，第一行包含整数 n。
第二行包含 n 个整数，表示整个数列。
10
2 5 1 7 10 6 9 4 3 8
 */

/* 输出：
第1小的元素：1
第2小的元素：2
第3小的元素：3
第4小的元素：4
第5小的元素：5
第6小的元素：6
第7小的元素：7
第8小的元素：8
第9小的元素：9
第10小的元素：10
 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010;

int q[N];

int quick_select(int q[], int l, int r, int k)
{
    int i = l - 1, j = r + 1, x = q[l + r >> 1];

    while (i < j)
    {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }

    if (k - 1 == j) return q[j];
    else if (k - 1 < j)  return quick_select(q, l, j, k);
    else return quick_select(q, j + 1, r, k);
}


int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    for (int k = 1; k <= n; ++k)
    {
        int res { quick_select(q, 0, n - 1, k) };
        printf("第%d小的元素：%d\n", k, res);
    }

    return 0;
}