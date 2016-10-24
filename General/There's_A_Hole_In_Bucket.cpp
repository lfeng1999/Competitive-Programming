#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[101];
int bucket[101];

int main()
{
	int M = 0, N = 0;
	cin >> M >> N;
	while (M != 0)
	{
		for (int i = 0; i != 101; ++i)
		{
			dp[i] = 9999999;
			bucket[i] = 0;
		}
		for (int i = 0; i != N; ++i)
		{
			cin >> bucket[i];
			dp[bucket[i]] = 1;
		}
		for (int i = 0; i != 101; ++i)
		for (int j = 0; j != N; ++j)
		if (i - bucket[j] >= 0)
			dp[i] = min(dp[i], dp[i - bucket[j]] + 1);
		if (dp[M] != 9999999)
			cout << dp[M] << endl;
		else
			cout << -1 << endl;
		cin >> M >> N;
	}
	return 0;
}