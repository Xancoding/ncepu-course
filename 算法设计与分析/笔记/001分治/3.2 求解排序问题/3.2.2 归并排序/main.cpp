/* 问题描述：
给定你一个长度为 n 的整数数列。
请你使用归并排序对这个数列按照从小到大进行排序。
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

int q[N], tmp[N];

void merge_sort(int q[] ,int l, int r) {
    if (l == r) return ;

    int mid = l + r >> 1;
    merge_sort(q, l, mid), merge_sort(q, mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }

    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (int i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];

}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    merge_sort(q, 0, n - 1);

    for (int i = 0; i < n; i++) printf("%d ", q[i]);

    return 0;
}