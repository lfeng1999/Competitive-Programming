#include <iostream>
#include <vector>

using namespace std;

vector<int> santa[31];
int N, n, a;

void recursion(int gifts[31], int a, bool used[31])
{
	if (a == N)
	{
		for (int i = 0; i != N; ++i)
			cout << gifts[i] << " ";
		exit(0);
	}
	for (int i = 0; i != santa[a].size(); ++i)
	{
		if (!used[santa[a][i]])
		{
			gifts[a] = santa[a][i];
			used[santa[a][i]] = true;
			recursion(gifts, a+1, used);
			used[santa[a][i]] = false;
		}
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> n;
		for (int j = 0; j != n; ++j)
		{
			cin >> a;
			santa[i].push_back(a);
		}
	}
	int gifts[31];
	bool used[31];
	for (int i = 0; i != 31; ++i)
		used[i] = false;
	for (int k = 0; k != santa[0].size(); ++k)
	{
		gifts[0] = santa[0][k];
		used[santa[0][k]] = true;
		recursion(gifts, 1,used);
		used[santa[0][k]] = false;
	}


	return 0;
}