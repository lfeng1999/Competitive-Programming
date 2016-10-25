#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int T, N, B, c, v, t, dp[3010][6];
vector<pair<int, int>> types[6];

int main()
{
	scanf("%d%d", &T, &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d%d%d", &c, &v, &t);
		types[t].push_back(make_pair(c, v));
	}
	scanf("%d", &B);
	for (int i = 1; i <= T; ++i)
	for (int j = 0; j != types[i].size(); ++j)
	for (int k = 1; k <= B; ++k)
		if (k >= types[i][j].first)
			dp[k][i] = max(dp[k][i], dp[k - types[i][j].first][i-1] + types[i][j].second);
	cout << dp[B][T];
	return 0;
}