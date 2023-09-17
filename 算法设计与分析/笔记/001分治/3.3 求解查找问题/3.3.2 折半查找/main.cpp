/* 输入：
输入共两行，第一行包含整数 n，k。n 表示数组的长度，k 表示待查找的元素
第二行包含 n 个整数，表示整个数列。
10 6
1 2 3 4 5 6 7 8 9 10
 */

/* 输出：

 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1010;

int n, k;
int a[N];
int cur;

int binarySearch(int a[], int l, int r, int k)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (a[mid] == k)
        {
            cur = mid;
            return mid;
        }
        else if (a[mid] < k) l = mid + 1;
        else r = mid - 1;
    }

    return -1;
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];

    int res{binarySearch(a, 0, n - 1, k) };

    if (res == -1) cout << "未找到" << k << "元素\n";
    else printf("a[%d] = %d", cur, k);

    return 0;
}