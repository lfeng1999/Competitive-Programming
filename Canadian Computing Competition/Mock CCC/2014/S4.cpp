#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> p1;
vector<int> p2;
vector<int> edges[40010];
int N, M, c1, c2;
bool visited[40010];

bool dfs(int c)
{
	visited[c] = true;
	if (c == N)
		return true;
	for (int i = 0; i != edges[c].size(); ++i)
	{
		if (!visited[edges[c][i]])
		{
			if (dfs(edges[c][i]))
			{
				p1.push_back(edges[c][i]);
				return true;
			}
		}
	}
	return false;
}

bool dfs2(int c)
{
	visited[c] = true;
	if (c == N)
		return true;
	for (int i = edges[c].size()-1; i >= 0; --i)
	{
		if (!visited[edges[c][i]])
		{
			if (dfs2(edges[c][i]))
			{
				p2.push_back(edges[c][i]);
				return true;
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 0; i != M; ++i)
	{
		scanf("%d%d", &c1, &c2);
		edges[c1].push_back(c2);
		edges[c2].push_back(c1);
	}
	
	dfs(1);
	memset(visited, false, sizeof(visited));
	dfs2(1);
	if (p1 != p2)
		cout << "Yes";
	else
		cout << "No";

	return 0;
}