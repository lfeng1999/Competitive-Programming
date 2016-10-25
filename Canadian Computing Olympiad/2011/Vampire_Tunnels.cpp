#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

queue<int> tunnels;
vector<pair<int, pair<int, int>>> edges[1601];   //other point, pair<time takes, if under sun>

vector<pair<int, int>> track[1601]; //dist, suntime

bool inq[1601];
int S = 0, N = 0, E = 0;

int main()
{
	//ifstream file("VampTunnel.txt");
	cin >> S >> N >> E;

	for (int i = 0; i != E; ++i)
	{
		int node1 = 0, node2 = 0, dist = 0, sun = 0;
		cin >> node1 >> node2 >> dist >> sun;
		edges[node1].push_back(make_pair(node2, make_pair(dist, sun)));
		edges[node2].push_back(make_pair(node1, make_pair(dist, sun)));
	}
	tunnels.push(0);
	track[0].push_back(make_pair(0, 0));
	inq[0] = true;
	while (!tunnels.empty())
	{
		int node = tunnels.front();
		for (int i = 0; i != track[node].size(); ++i)
		for (int j = 0; j != edges[node].size(); ++j)
		{
			bool pos = true;
			for (int k = 0; k != track[edges[node][j].first].size(); ++k)
			{
				if (track[edges[node][j].first][k].first <= track[node][i].first + edges[node][j].second.first && track[edges[node][j].first][k].second <= track[node][i].second + edges[node][j].second.first*edges[node][j].second.second)
				{
					pos = false;
					break;
				}
			}


			if (track[node][i].second + edges[node][j].second.first*edges[node][j].second.second <= S && pos)
			{
				track[edges[node][j].first].push_back(make_pair(track[node][i].first + edges[node][j].second.first, track[node][i].second + edges[node][j].second.first*edges[node][j].second.second));
				if (!inq[edges[node][j].first])
				{
					inq[edges[node][j].first] = true;
					tunnels.push(edges[node][j].first);
					//cout << node << " " << edges[node][j].first << " " << track[node][i].first + edges[node][j].second.second << " " << track[node][i].second + edges[node][j].second.first*edges[node][j].second.second << endl;
				}
			}
		}
		tunnels.pop();
		inq[node] = false;
	}
	int dist = 1000000000;
	for (int i = 0; i != track[N - 1].size(); ++i)
	{
		if (dist > track[N - 1][i].first)
			dist = track[N - 1][i].first;
	}
	if (dist == 1000000000)
		cout << -1;
	else
		cout << dist;
	return 0;
}