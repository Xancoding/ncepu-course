/* 输入：
4 31
11 13 24 7
 */

/* 输出：
第 1 个解选取的数为：
11 13 7
第 2 个解选取的数为：
24 7
 */

#include <iostream>
using namespace std;
const int N = 1010;

int n, m;
int a[N];  // 集合
int cnt;   // 解的个数

void dispOption(int op[])
{
    ++cnt;
    cout << "第 " << cnt << " 个解选取的数为：\n";
    for (int i = 1; i <= n; ++i)
    {
        if (op[i])
        {
            cout << a[i] << ' ';
        }
    }
    cout << '\n';
}

/* 参数：递归层数、当前整数和、该层及以下的所有整数和、解向量
 */
void dfs(int i, int cw, int rw, int op[])
{
    // 递归出口
    if (i > n)
    {
        if (cw == m)
        {
            dispOption(op);
        }
    }
    else
    {
        if (cw + a[i] <= m)  // 左剪枝
        {
            op[i] = 1;
            dfs(i + 1, cw + a[i], rw - a[i], op);
        }
        if (cw + rw - a[i] >= m)  // 右剪枝
        {
            op[i] = 0;
            dfs(i + 1, cw, rw - a[i], op);
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int rw{ 0 };    // 所有整数和
    for (int i = 1; i <= n; ++i) rw += a[i];

    int op[N];  // 解向量
    dfs(1, 0, rw, op);

    return 0;
}