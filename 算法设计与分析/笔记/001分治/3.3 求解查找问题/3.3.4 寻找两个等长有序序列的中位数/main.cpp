/* 问题描述：
 * 对于一个长度为 n 的有序序列（假设均为升序序列）a，处于中间位置的元素称为 a 的中位数
 * 如果一共有奇数个数，则中位数是最中间的数；如果一共有偶数个数，则中位数是中间偏左的数。
 * 设计一个算法求给定的两个有序序列的中文数
 */

/* 输入：
输入共三行，第一行包含整数 n。
第二行包含 n 个整数，表示数列 a。
第三行包含 n 个整数，表示数列 b。
5
11 13 15 17 19
2 4 6 8 20
 */

/* 输出：
中位数为：11
 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1010;

int n;
int a[N], b[N];
int m1, m2;

void prePart(int &l, int &r)  // 求序列的前半子序列
{
    r = (l + r) >> 1;
}

void postPart(int &l, int &r)  // 求序列的后半子序列
{
    int m{ (l + r) >> 1 };
    if ((l + r) % 2 == 0)      // 序列中有奇数个元素
        l = m;
    else                       // 序列中有偶数个元素
        l = m + 1;
}
int getMidNum(int a[], int la, int ra, int b[], int lb, int rb)
{
    if (la == ra && lb == rb)   // 两个序列都只有一个元素，返回较小者
    {
        return a[la] < b[lb] ? a[la] : b[lb];
    }
    else
    {
        m1 = (la + ra) >> 1;      // 序列 a 的中位数
        m2 = (lb + rb) >> 1;      // 序列 b 的中位数

        // 保证舍弃的部分长度相同
        if (a[m1] == b[m2])     // 两中位数相等时返回该中位数
        {
            return a[m1];
        }
        else if (a[m1] < b[m2])
        {
            postPart(la, ra);  // a 取后半部分
            prePart(lb, rb);   // b 取前半部分
            return getMidNum(a, la, ra, b, lb, rb);
        }
        else
        {
            prePart(la, ra);    // a 取前半部分
            postPart(lb, rb);   // b 取后半部分
            return getMidNum(a, la, ra, b, lb, rb);
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    cout << "中位数为：" << getMidNum(a, 0, n - 1, b, 0, n - 1) << '\n';

    return 0;
}