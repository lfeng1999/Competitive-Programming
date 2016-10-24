#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

vector<pair<int, int>> paths[100001];
int high = 0;

void branch(int node, int cost)
{
	int size = paths[node].size();
	if (size == 0)
	{
		high = max(high, cost);
	}
	else
	{
		for (int i = 0; i != paths[node].size(); ++i)
		{
			branch(paths[node][i].first, cost + paths[node][i].second);
		}
	}
}



int main()
{
	//ifstream file("Santa.txt");

	int N = 0;
	cin >> N;
	int total = 0;
	for (int i = 0; i != N; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		paths[a].push_back(make_pair(b, c));
		total += c * 2;
	}

	branch(0, 0);

	cout << total - high;
	
	return 0;
}