// 给定若干正整数，从中选出若干个数，使他们的和恰好为 k，要求找出个数最少的解
#include <iostream>
using namespace std;
const int N = 20, INF = 0x3f3f3f3f;
int k = 15;
int n = 5;
int a[] = { 2, 6, 9, 8, 5 };
int bestx[N];  // 最优解向量 ，存值 
int minNum = INF;  // 解向量最少个数 

void dfs(int level, int sum, int num, int x[])
{
	if (sum == k && num < minNum)
	{
		minNum = num;
		for (int i = 0; i < num; ++i) bestx[i] = x[i];	
	}	
	else 
	{
		for (int i = level; i < n; ++i) 
		{
			// 左剪枝 
			if (a[level] + sum <= k)
			{
				x[num] = a[i];
				dfs(level+1, sum+a[level], num+1, x);
				x[num] = 0;
			}
			
			// 右子树 
			dfs(level+1, sum, num, x);
		}
	}
} 

int main()
{
	int x[N] = { 0 };
	dfs(0, 0, 0, x);
	
	cout << "解向量最小个数：" << minNum << '\n';
	for (int i = 0; i < minNum; ++i) cout << bestx[i] << ' ';
	cout << '\n'; 

	return 0;	
} 