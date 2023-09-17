/* 问题描述：
 * 设 A 和 B 是两个字符串，现在要用最少的字符操作次数将字符串 A 转换为字符串 B。这里所说的字符操作共有以下 3 种
 * （1）删除一个字符。
 * （2）插入一个字符。
 * （3）将一个字符替换为另一个字符。
 */

/* 输入：
第一行包含两个整数 N 和 M。
第二行包含一个长度为 N 的字符串，表示字符串 A。
第三行包含一个长度为 M 的字符串，表示字符串 B。
7 5
sfdqxbw
gfdgw
 */

/* 输出：
最少的字符操作次数：4
 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1010;

int la, lb;
char a[N], b[N];
int f[N][N];    // a[0..i] 转换为 b[0..j] 的最少操作次数

int main()
{
    cin >> la >> lb;
    scanf("%s%s", a + 1, b + 1);

    for (int i = 1; i <= la; i++) f[i][0] = i;
    for (int i = 1; i <= lb; i++) f[0][i] = i;

    /* f[i - 1][j] + 1                  删除a[i]
     * f[i][j - 1] + 1                  在 a[i] 后插入b[j]
     * f[i - 1][j - 1] + (a[i] != b[j]) 替换 a[i] 成为 b[j]
     */
    for (int i = 1; i <= la; i++)
        for (int j = 1; j <= lb; j++)
        {
            f[i][j] = min(f[i - 1][j], f[i][j - 1]) + 1;
            if (a[i] == b[j]) f[i][j] = min(f[i][j], f[i - 1][j - 1]);
            else f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }

    cout << "最少的字符操作次数：" << f[la][lb] << '\n';
}


