#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int,int>> graph[5001];

bool inq[5001];

int cost[5001], N = 0, T = 0, K = 0, D = 0;

queue<int> path;

int main()
{
	fill_n(cost, 5000, 1000000);
	//ifstream file("shipandshop.txt");

	scanf("%d%d",&N,&T);
	for (int i = 0; i != T; ++i)
	{
		int x = 0, y = 0, cost = 0;
		scanf("%d%d%d",&x,&y,&cost);
		graph[x - 1].push_back(make_pair(y - 1, cost));
		graph[y - 1].push_back(make_pair(x - 1, cost));
	}
	scanf("%d",&K);
	for (int i = 0; i != K; ++i)
	{
		int z = 0, Pz = 0;
		scanf("%d%d",&z,&Pz);
		cost[z - 1] = Pz;
		path.push(z - 1);
		inq[z - 1] = true;
	}
	scanf("%d",&D);
	while (!path.empty())
	{
		int spot = path.front();
		for (int i = 0; i != graph[spot].size(); ++i)
		{
			if (cost[graph[spot][i].first] > cost[spot] + graph[spot][i].second)
			{
				cost[graph[spot][i].first] = cost[spot] + graph[spot][i].second;
				if (!inq[graph[spot][i].first])
				{
					inq[graph[spot][i].first] = true;
					path.push(graph[spot][i].first);
				}
			}
		}
		path.pop();
		inq[spot] = false;
	}
	printf("%d",cost[D-1]);

	return 0;
}