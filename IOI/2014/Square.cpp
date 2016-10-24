#include <iostream>
#include <algorithm>

int grid[1001][1001];

using namespace std;

int main()
{
	int N = 0, maxi = 1, mc=0;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			cin >> grid[i][j];
			if (grid[i][j])
				++mc;
		}
	}
	for (int i = 0; i != N - 1; ++i)
	{
		for (int j = 0; j != N - 1; ++j)
		{
			if ((grid[i][j]) && (grid[i + 1][j]) && (grid[i][j + 1]) && (grid[i + 1][j + 1]))
			{
				grid[i + 1][j + 1] = min(min(grid[i][j], grid[i + 1][j]), grid[i][j + 1]) + 1;
				if (grid[i + 1][j + 1] > maxi)
				{
					maxi = grid[i + 1][j + 1];
					mc = 1;
				}
				else if (grid[i + 1][j + 1] == maxi && maxi != 1)
					++mc;
			}
		}
	}
	//for (int i = 0; i != N; ++i)
	//{
	//	for (int j = 0; j != N; ++j)
	//	{
	//		cout << grid[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cout << maxi*mc;
	return 0;
}