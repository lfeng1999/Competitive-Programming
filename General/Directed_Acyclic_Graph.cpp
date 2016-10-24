#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

typedef pair<int, int> PII;

vector<int> paths[1001];
bool passed[1001], checked[1001];
int N = 0;


void cycle(int start, bool past[1001])
{
	for (int i = 0; i != paths[start].size(); ++i)
	{
		if (!checked[start])
		{
			if (past[paths[start][i]])
			{
				cout << "NO";
				exit(0);
			}
			past[paths[start][i]] = true;
			cycle(paths[start][i], past);
			past[paths[start][i]] = false;
			checked[start] = true;
		}
	}
	return;
}

int main()
{
	ifstream file("Acyclic.txt");
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	for (int j = 0; j != N; ++j)
	{
		int x;
		scanf("%d",&x);
		if (x)
		{
			paths[i].push_back(j);
		}
	}
	for (int i = 0; i != N; ++i)
	{
		if (paths[i].size() > 0)
		{
			passed[i] = true;
			cycle(i, passed);
			passed[i] = false;
			checked[i] = true;
		}
	}
	cout << "YES";


	return 0;
}