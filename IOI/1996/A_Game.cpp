#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N = 0, game[201], states[201][201], psums[201];

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
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> game[i];
		psums[i] = game[i];
		if (i)
			psums[i] += psums[i-1];
	}
	int x = dp(0, N - 1);
	cout << x << " " << psums[N - 1] - x;
	return 0;
}