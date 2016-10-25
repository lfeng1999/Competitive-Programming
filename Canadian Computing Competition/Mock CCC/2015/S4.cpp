#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define rint(a) scanf("%d",&a)
#define rll(a) scanf("%lld",&a)

const int MAXN = 100010;
int d[MAXN], w[MAXN], N;
long long dp[MAXN], dp2[MAXN], dp3[MAXN], dp4[MAXN];

int main()
{
	rint(N);
	for (int i = 1; i <= N; ++i)
	{
		rint(d[i]);
		rint(w[i]);
	}
	dp[1] = d[1];
	dp2[1] = max(d[1] - w[2], 0);
	dp3[1] = d[1];
	dp4[1] = max(d[1] - w[2], 0);
	for (int i = 2; i <= N; ++i)
	{
		dp[i] = max(d[i] - w[i - 1], 0) + min(dp[i - 1], dp3[i - 1]);
		dp2[i] = max(d[i] - w[i + 1], 0) + min(dp2[i - 1], dp4[i - 1]);
		dp3[i] = d[i] + min(dp2[i - 1], dp4[i - 1]);
		dp4[i] = max(d[i] - w[i - 1] - w[i + 1], 0) + min(dp[i - 1], dp3[i - 1]);
	}
	cout << min(dp[N],dp3[N]);
	return 0;
}