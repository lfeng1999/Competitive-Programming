#include <iostream>
#include <vector>

using namespace std;

int N, nedge = 0, visited[1000];
vector<int> edges[1000];

void cycle(int n)
{
	visited[n] = true;
	for (int i = 0; i != edges[n].size(); ++i)
	{
		if (!visited[edges[n][i]])
		{
			--nedge;
			cycle(edges[n][i]);
		}
	}
}


int main()
{
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	for (int j = 0; j != N; ++j)
	{
		int val;
		scanf("%d", &val);
		if (val)
		{
			edges[i].push_back(j);
			++nedge;
		}
	}
	nedge /= 2;

	for (int i = 0; i != N; ++i)
	{
		if (!visited[i])
		{
			cycle(i);
//			cout << i << endl;
		}
	}
	//for (int i = 0; i != N; ++i)
	//{
	//	for (int j = 0; j != edges[i].size(); ++j)
	//		cout << i << " " << edges[i][j] << endl;
	//}
	cout << nedge;
	return 0;
}