#include <iostream>

using namespace std;

int R, C;

char city[1001][1001];
int grid[1001][1001];

void flood(int r, int c, int val)
{
	if (!grid[r][c])
	{
		grid[r][c] = val;
		if (r > 0 && city[r - 1][c] == 'S')
			flood(r - 1, c, val);
		if (c > 0 && city[r][c - 1] == 'E')
			flood(r, c - 1, val);
		if (r < R - 1 && city[r + 1][c] == 'N')
			flood(r + 1, c, val);
		if (c < C - 1 && city[r][c + 1] == 'W')
			flood(r, c + 1, val);
		if (city[r][c] == 'S' && !grid[r + 1][c])
				flood(r + 1, c, val);
		else if (city[r][c] == 'N' && !grid[r - 1][c])
				flood(r - 1, c, val);
		else if (city[r][c] == 'W' && !grid[r][c - 1])
				flood(r, c - 1, val);
		else if (city[r][c] == 'E' && !grid[r][c + 1])
			flood(r, c + 1, val);
	}
}

int main()
{
	scanf("%d%d", &R, &C);
	for (int i = 0; i != R; ++i)
	for (int j = 0; j != C; ++j)
		scanf(" %c", &city[i][j]);

	int val = 1;

	for (int i = 0; i != R; ++i)
		for (int j = 0; j != C; ++j)
			if (grid[i][j] == 0)
			{
				flood(i, j, val);
				++val;
			}
	cout << val - 1;
	return 0;
}