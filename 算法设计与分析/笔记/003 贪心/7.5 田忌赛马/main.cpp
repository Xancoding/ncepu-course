/* 问题描述：
 * 现在双方各 n 匹马，依次派出一匹马进行比赛，
 * 每一轮获胜的一方将从输的一方得到 200 银币，
 * 平局则不用出钱，田忌已知所有马的速度值并可以安排出场次序，
 * 问他如何安排比赛获得的银币最多？
 */

/* 求解思路：
 * 田忌的马的速度用数组 a 表示，齐威王的用数组 b 表示
 * 将 a、b 数组递增排序，采用贪心思路分情况讨论
 */

/* 输入：
3
92 83 71
95 87 74
 */

/* 输出：

 */

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n;     // 马的数量
int a[N];  // 田忌
int b[N];  // 齐威王

int main()
{
    cout << "马的数量：\n";
    cin >> n;

    cout << "田忌的马：\n";
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << "齐威王的马：\n";
    for (int i = 0; i < n; ++i) cin >> b[i];
    sort(a, a + n);
    sort(b, b + n);

    int res{ 0 };  // 田忌赢钱获得的银币
    int la{ 0 }, ra{ n - 1 };
    int lb{ 0 }, rb{ n - 1 };
    while (la <= ra)
    {
        if (a[ra] > b[rb])      // 田忌最快的马比齐威王最快的马快，最快比最快，赢 200
        {
            --ra;
            --rb;
            res += 200;
        }
        else if (a[ra] < b[ra])  // 田忌最快的马比齐威王最快的马慢（必输），最慢比最快，输 200
        {
            ++la;
            --rb;
            res -= 200;
        }
        else                    // 田忌最快的马与齐威王最快的马一样快
        {
            if (a[la] > b[lb])  // 田忌最慢的马比齐威王最慢的马快，最慢比最慢，赢 200
            {
                ++la;
                ++lb;
                res += 200;
            }
            else   // 田忌最慢的马比齐威王最慢的马慢或一样快（必输），最慢比最快，输 200
            {
                if (a[la] < b[rb])
                {
                    res -= 200;
                }
                ++la;
                --rb;
            }
        }
    }

    cout << "田忌获得银元：" << res << '\n';

    return 0;
}