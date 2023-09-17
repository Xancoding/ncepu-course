/* 资源分配问题：
 * 某公司有 3 个商店A、B、C，拟将新招聘的 5 名员工分配给这 3 个商店
 * 给出各个商店得到新员工后每年的盈利情况
 * 求分配给各商店各多少员工才使公司盈利最大
 */

/* 分配员工数和盈利情况
 *      0    1      2       3       4       5
 * A    0    3      7       9       12      13
 * B    0    5      10      11      11      11
 * C    0    4      6       11      12      12
 */

/* 输入
 * 第一行两个整数，N，V，用空格隔开，分别表示商店数量和总人数。
 * 接下来有 N 行，每行两个整数 wi，用空格隔开，分别表示投入 i 个人的盈利。
3 5
0 3 7 9 12 13
0 5 10 11 11 11
0 4 6 11 12 12
 */

/* 输出
 * 最优资源分配方案如下：
 * C商店分配1人
 * B商店分配2人
 * A商店分配2人
 * 该方案的总盈利为：21万元
 */

#include <iostream>

using namespace std;

const int N = 1010;

int n, m;        // 商店数量、员工数
int f[N][N];     // 前 i 个商店，员工数为 j，最大盈利
int w[N][N];     // 商店 i 投入 j 个人的盈利
int num[N][N];   // 有 i 个商店，员工数总数为 j 时，商店 i 的员工数

void dispOption()
{
    int k{ m };
    cout << "最优资源分配方案如下：\n";
    for (int i = n; i >= 1; --i)
    {
        cout << char('A' + i - 1) << "商店分配" << num[i][k] << "人\n";
        k -= num[i][k];
    }
}

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            cin >> w[i][j];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= j; ++k)
            {
                if (f[i][j] < f[i - 1][j - k] + w[i][k])
                {
                    f[i][j] = f[i - 1][j - k] + w[i][k];
                    num[i][j] = k;
                }
            }

    dispOption();
    cout << "该方案的总盈利为：" << f[n][m] << "万元\n";
}
