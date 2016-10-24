#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N = 0, game[1001], states[1001][1001], psums[1001];

int sum(int i, int j)
{
	if (i)
		return psums[j] - psums[i - 1];
	else
		return psums[j];
}

int dp(int i, int j)
{
	if (i == j)
		return game[i];
	if (states[i][j])
		return states[i][j];

	int c1 = sum(i, j) - dp(i + 1, j);
	int c2 = sum(i, j) - dp(i, j-1);
	states[i][j] = max(c1, c2);
	return max(c1,c2);
}



int main()
{
	//ifstream file("game.txt");
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &game[i]);
		psums[i] = game[i];
		if (i)
			psums[i] += psums[i-1];
	}
	cout << dp(0, N - 1);
	return 0;
}