/* 问题描述：
给定你一个长度为 n 的整数数列。
请你使用快速排序对这个数列按照从小到大进行排序。
并将排好序的数列按顺序输出。
 */

/* 输入：
输入共两行，第一行包含整数 n 。
第二行包含 n 个整数，表示整个数列。
5
3 1 2 4 5
 */

/* 输出：
1 2 3 4 5
 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010;

int a[N];

void quick_sort(int a[], int l, int r) {
    if (l == r) return ;

    int i = l - 1, j = r + 1, x = a[l + r >> 1];

    while(i < j) {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }

    // q[l..j] <= x, q[j+1..r] >= x
    quick_sort(a, l, j), quick_sort(a, j + 1, r);
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    quick_sort(a, 0, n - 1);

    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}


