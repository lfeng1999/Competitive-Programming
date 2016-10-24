#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

vector<int> graph[20001];

bool past[20001];
int size[20001];
int order[20001];

int counter = 0;

int dfs(int node)
{
	int count = 1;
	past[node] = true;
	order[node] = counter;
	++counter;
	for (int i = 0; i != graph[node].size(); ++i)
	{
		if (!past[graph[node][i]])
		{
			count += dfs(graph[node][i]);

		}
	}
	size[node] = count;

	return count;
}


int main()
{
	//ifstream file("Balancing.txt");
	int N = 0;
	scanf("%d", &N);
	for (int i = 0; i != N-1; ++i)
	{
		int n1, n2;
		scanf("%d%d", &n1,&n2);
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}
	int maxn = 0, minn = 100000;
	int node = 0;
	dfs(1);
	for (int i = 1; i <= N; ++i)
	{
		maxn = 0;
		for (int j = 0; j != graph[i].size(); ++j)
		{
			if (order[i] < order[graph[i][j]])
				maxn = max(maxn, size[graph[i][j]]);
			else
				maxn = max(maxn, N - size[i]);
		}
		if (maxn < minn)
		{
			minn = maxn;
			node = i;
		}
	}
	cout << node << " " << minn;



	return 0;
}