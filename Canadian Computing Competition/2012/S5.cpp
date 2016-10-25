#include <iostream>

int grid[26][26];
int fix[26][26];

using namespace std;

int main()
{
	int r = 0, c = 0, n = 0;
	cin >> r >> c >> n;
	for (int i = 0; i != n; ++i)
	{
		int x = 0, y = 0;
		cin >> x >> y;
		fix[x][y] = -1;
	}
	
	grid[0][1] = 1;
	for (int i = 1; i != r + 1; ++i)
	{
		for (int j = 1; j != c + 1; ++j)
		{
			if (fix[i][j] != -1)
				grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
		}
	}
	cout << grid[r][c];
	return 0;
}