#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

bool edges[26][26];

bool run()
{
	queue<int> Q;
	bool visited[26];
	for (int i = 0; i != 26; ++i)
		visited[i] = false;
	Q.push(0);
	while (!Q.empty())
	{
		int p = Q.front(); Q.pop();
		for (int i = 0; i != 26; ++i)
		{
			if (edges[p][i] && !visited[i])
			{
				if (i == 1) return true;
				visited[i] = true;
				Q.push(i);
			}
		}
	}
	return false;
}

int main()
{
	string road = "";
	while (road != "**")
	{
		cin >> road;
		edges[road[0] - 65][road[1] - 65] = true;
		edges[road[1] - 65][road[0] - 65] = true;
	}
	int nstreet = 0;
	for (int i = 0; i != 25; ++i)
	{
		for (int j = i + 1; j != 26; ++j)
		{
			if (edges[i][j])
			{
				edges[i][j] = false; edges[j][i] = false;
				if (!run())
				{
					++nstreet;
					cout << char(i + 65) << char(j + 65) << endl;
				}
				edges[i][j] = true; edges[j][i] = true;
			}
		}
	}
	printf("There are %d disconnecting roads.", nstreet);
	return 0;
}