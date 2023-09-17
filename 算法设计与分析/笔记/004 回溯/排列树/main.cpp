// 1~n n个整数中取出  m 个元素的排列 
#include <iostream>
#include <queue>
using namespace std;
const int N = 20;
int n=3, m=2;

void dfs(int level, int x[], int flag[])
{
	if (level == m+1)
	{
		for (int i = 1; i <= m; ++i) 
		{
			if (x[i])
			{
				cout << x[i] << ' '; 
			}
		}
		cout << '\n';
	}
	else 
	{
		for (int i = 1; i <= n; ++i) 
		{
			if (flag[i] == 0)
			{
				x[level] = i;
				flag[i] = 1;
				dfs(level+1, x, flag);
				x[level] = 0;
				flag[i] = 0;
			}
		}
	}
	
}

int main()
{
	int x[N]={ 0 };	
	int flag[N]={ 0 };
	
	dfs(1, x, flag);
	
	return 0;
}