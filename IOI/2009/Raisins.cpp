#include <iostream>
#include <algorithm>

using namespace std;

int raisin[52][52], psum[52][52], dp[52][52][52][52];
int N, M;

int solve(int i, int j, int k, int l)
{
	if (dp[i][j][k][l])
		return dp[i][j][k][l];
	if (i == j && k == l)
		return 0;
	int minv = 0x7fffffff;
	for (int a = i; a != j; ++a)
		minv = min(minv, solve(i, a, k, l) + solve(a + 1, j, k, l));
	for (int a = k; a != l; ++a)
		minv = min(minv, solve(i, j, k, a) + solve(i, j, a + 1, l));
	dp[i][j][k][l] = minv + psum[j][l] - psum[i - 1][l] - psum[j][k - 1] + psum[i - 1][k - 1];
	return dp[i][j][k][l];
}


int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	for (int j = 1; j <= M; ++j)
	{
		cin >> raisin[i][j];
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			psum[i][j] = raisin[i][j] + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
		}
	}
	cout << solve(1, N, 1, M);
	return 0;
}