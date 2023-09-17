/* 问题描述：
 * 给定两个长度分别为 N 和 M 的字符串 A 和 B，求既是 A 的子序列又是 B 的子序列的字符串长度最长是多少
 */

/* 输入：
第一行包含两个整数 N 和 M。
第二行包含一个长度为 N 的字符串，表示字符串 A。
第三行包含一个长度为 M 的字符串，表示字符串 B。
字符串均由小写字母构成。
6 9
abcbdb
acbbabdbb
 */

/* 输出：
最长公共子序列：acbdb
长度：5
 */
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;

const int N = 1010;

int n, m;
int f[N][N];    // a、b 中从头开始的长度分别为 i、j 的子序列的 LCS 长度
char a[N], b[N];
stack<char> LCS;


/*
 * 功能：输出 LCS
 */
void dispLCS()
{
    int k{ f[n][m] };
    int i{ n };
    int j{ m };
    while (k > 0)
    {
        if (f[i][j] == f[i - 1][j])
        {
            --i;
        }
        else if (f[i][j] == f[i][j - 1])
        {
            --j;
        }
        else
        {
            LCS.push(a[i]);
            --i;
            --j;
            --k;
        }
    }

    cout << "最长公共子序列：";
    for (int i = 1; i <= f[n][m]; ++i)
    {
        cout << LCS.top();
        LCS.pop();
    }

    cout << '\n';
}

int main() {
    cin >> n >> m;

    scanf("%s%s", a + 1, b + 1);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);                         // a[i] != b[j]
            if (a[i] == b[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);   // a[i] = b[j]
        }

    dispLCS();
    cout << "长度：" << f[n][m] << endl;

    return 0;
}