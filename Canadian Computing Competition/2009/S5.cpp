#include <iostream>
#include <algorithm>

int grid[30006][1006];
int shop[1001][4];

using namespace std;

int main()
{
	int R = 3, C = 5, K = 3;
	cin >> R >> C >> K;
	for (int i = 0; i != R + 4; ++i)
	{
		for (int j = 0; j != C + 4; ++j)
		{
			grid[i][j] = 0;
		}
	}
	for (int i = 0; i != K; ++i)
	for (int j = 0; j != 4; ++j)
		cin >> shop[i][j];

	for (int p = 0; p != K; ++p)
	for (int i = max(0, shop[p][1] - shop[p][2] - 1); i != min(R, shop[p][1] + shop[p][2]); ++i) // maybe -1 in min(R,-1)
	{
		int welp = sqrt(shop[p][2] * shop[p][2] - (shop[p][1] - i - 1)*(shop[p][1] - i - 1));
		int x = max(0, shop[p][0] - 1 - welp);
		grid[i][x] += shop[p][3];
		int x2 = min(C , shop[p][0] + welp);
		grid[i][x2] -= shop[p][3];
	}
	
	int bitmax = 0, bitcount = 0;
	bitmax = grid[0][0];
	for (int i = 0; i != R; ++i)
	{
		for (int j = 0; j != C; ++j)
		{
			if (j)
				grid[i][j] += grid[i][j - 1];
			if (bitmax == grid[i][j])
				++bitcount;
			else if (bitmax < grid[i][j])
			{
				bitmax = max(grid[i][j], bitmax);
				bitcount = 1;
			}
		}
	}

	cout << bitmax;
	cout << endl;
	cout << bitcount;
	return 0;
}