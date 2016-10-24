#include <iostream>
#include <vector>

using namespace std;

vector<int> graph[101];
int dp[101][101];

int run(int point, int K)
{
	if (K == 0)
		return 1;
	if (dp[point][K])
		return dp[point][K];
	int total = 0;
	for (int i = 0; i != graph[point].size(); ++i)
		total += run(graph[point][i], K - 1);
	dp[point][K]=total;
	return total;
}

int main()
{
	int N = 0, K = 0;
	scanf("%d%d", &N, &K);
	for (int i = 0; i != N; ++i)
	for (int j = 0; j != N; ++j)
	{
		int n;
		scanf("%d", &n);
		if (n)
			graph[i].push_back(j);
	}
	int total = 0;
	for (int i = 0; i != N; ++i)
		total += run(i, K);
	cout << total;
	return 0;
}