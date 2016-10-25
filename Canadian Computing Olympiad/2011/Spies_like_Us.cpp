#include <iostream>
#include <vector>

using namespace std;

#define MAXN 2010

bool adj[MAXN][MAXN];
vector<int> connect[MAXN];

int N, M, K, A, B;

int main()
{
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i != K; ++i)
	{
		scanf("%d%d", &A, &B);
		for (int j = 0; j != connect[B].size(); ++j)
		{
			if (adj[A][connect[B][j]])
			{
				cout << "NO";
				return 0;
			}
			else
			{
				adj[A][connect[B][j]] = true;
				adj[connect[B][j]][A] = true;
			}
		}
		connect[B].push_back(A);
	}
	cout << "YES";
	return 0;
}