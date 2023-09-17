#include <iostream>
#include <queue>
using namespace std;
const int N = 20, INF = 0x3f3f3f3f;

// 问题表示
int n{ 3 }, m { 30 };
int v[] = { 0, 16, 15, 15 };  // 体积，下标为 0 的元素不使用
int w[] = { 0, 45, 25, 25 };  // 价值，下标为 0 的元素不使用

int maxw = -INF;  // 最大价值
int bestx[N];     // 最优解向量
int tot{ 1 };     // 解向量中的结点数累计

struct NodeType
{
    int number{};  // 结点编号
    int level{};   // 当前结点在搜索空间中的层次
    int v{};       // 当前结点的总体积
    int w{};       // 当前结点的总价值
    int x[N];      // 当前结点包含的解向量
    double ub{};   // 上界

    bool operator<(const NodeType& other) const {
        return ub < other.ub;
    }
};

// 计算分支结点 e 的上界
void bound(NodeType& e)
{
    int level{ e.level+1 };
    int sumv = e.v;     // 体积
    double sumw = e.w;  // 价值
    while ((sumv + v[level]) <= m && level <= n)
    {
        sumv += v[level];    // 已装入体积
        sumw += w[level];    // 已装入价值
        ++level;
    }
    
    if (level <= n)
        e.ub = sumw + (m - sumv) * w[level] / v[level];
    else 
        e.ub = sumw;
}

// 结点 e 进队
void enQueue(NodeType e, priority_queue<NodeType>& qu)
{
    // 叶结点
    if (e.level == n)
    {
        // 找到更大价值的结点
        if (e.w > maxw)
        {
            maxw = e.w;
            for (int i = 1; i <= n; ++i)
            {
                bestx[i] = e.x[i];
            }
        }
    }
    else 
        qu.push(e);
}

// 求解 01 背包最优解
void bfs()
{
    NodeType e, e1, e2;           // 定义 3 个结点
    priority_queue<NodeType> qu;  // 大根堆
    e.level = 0;                  // 根节点赋初值，层次记为 0
    e.w = 0, e.v = 0;
    e.number = tot++;

    for (int i = 1; i <= n; ++i) e.x[i] = 0;

    bound(e);        // 求根节点上界
    qu.push(e);  // 根节点入队

    while (!qu.empty())
    {
        e = qu.top();  qu.pop();
        // 左剪枝
        if (e.v + v[e.level+1] <= m)
        {
            // 建立左孩子结点
            e1.number = tot++;
            e1.level = e.level+1;
            e1.v = e.v + v[e1.level];
            e1.w = e.w + w[e1.level];

            // 复制解向量
            for (int i = 1; i <= n; ++i) e1.x[i] = e.x[i];
            e1.x[e1.level] = 1;
            bound(e1);           // 求上界
            enQueue(e1, qu);  // 入队
        }
        // 建立右孩子结点
        e2.number = tot++;
        e2.level = e.level+1;
        e2.v = e.v;
        e2.w = e.w;

        // 复制解向量
        for (int i = 1; i <= n; ++i) e2.x[i] = e.x[i];
        e2.x[e2.level] = 0;

        bound(e2);           // 求上界

        // 右剪枝
        if (e2.ub > maxw) enQueue(e2, qu);  // 入队
    }
}

int main()
{
    bfs();
    cout << "分支界限法：\n X=[ ";
    for (int i = 1; i <= n; ++i) cout << bestx[i] << ' ';
    cout << "],装入总价值为" << maxw << '\n';

    return 0;
}

