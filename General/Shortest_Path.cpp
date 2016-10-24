#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;

vector<pair<int, int>> graph[1001]; // point length

int N = 0, M = 0, a = 0, b = 0, c = 0;

int paths[1001];
bool inq[1001];

void dijkstra()
{
	queue<int> que;
	que.push(1);
	while (!que.empty())
	{
		int top = que.front();
		que.pop();
		inq[top] = false;
		for (int i = 0; i != graph[top].size(); ++i)
		{
			if (paths[top] + graph[top][i].second < paths[graph[top][i].first])
			{
				paths[graph[top][i].first] = paths[top] + graph[top][i].second;
				if (!inq[graph[top][i].first])
				{
					inq[graph[top][i].first] = true;
					que.push(graph[top][i].first);
				}
			}
		}
	}
}


int main()
{
	for (int i = 0; i != 1001; ++i)
		paths[i] = 99999999;
	paths[1] = 0;
	inq[1] = true;
	cin >> N >> M;
	for (int i = 0; i != M; ++i)
	{
		cin >> a >> b >> c;
		graph[a].push_back(make_pair(b, c));
	}
	dijkstra();
	cout << paths[N];
	return 0;
}