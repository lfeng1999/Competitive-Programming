#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[10001];
int coins[10001];

int main()
{
	int x = 0, n = 0;
	scanf("%d%d", &x, &n);
	for (int i = 0; i <= x; ++i)
		dp[i] = 99999;
	for (int i = 0; i != n; ++i)
	{
		scanf("%d", &coins[i]);
		dp[coins[i]] = 1;
	}
	for (int i = 0; i <= x; ++i)
		for (int k = 0; k != n; ++k)
			if (i - coins[k] >= 0)
				dp[i] = min(dp[i],dp[i - coins[k]] + 1);
	cout << dp[x];
	return 0;
}