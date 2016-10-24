#include <iostream>
#include <algorithm>

int grid[101][101];

using namespace std;

int main()
{
	int M = 0, N = 0;
	cin >> M >> N;

	int a = 0, b = 0;
	cin >> a >> b;
	while (a | b)
	{
		grid[a-1][b-1] = 1;
		cin >> a >> b;
	}

	for (int i = 1; i != M; ++i)
		grid[i][0] += grid[i - 1][0];
	for (int i = 1; i != N; ++i)
		grid[0][i] += grid[0][i - 1];

	for (int i = 1; i != M; ++i)
	for (int j = 1; j != N; ++j)
		grid[i][j] += max(grid[i - 1][j], grid[i][j-1]);
	cout << grid[M - 1][N - 1];
	return 0;
}