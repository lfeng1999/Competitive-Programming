#include <iostream>
#include <queue>
#include <algorithm>

int grid[25][25];
char maze[25][25];

using namespace std;

int main()
{
	int t = 1;
	cin >> t;
	for (int k = 0; k != t; ++k)
	{
		int row = 3, col = 5;
		cin >> row >> col;
		for (int i = 0; i != row; ++i)
		for (int j = 0; j != col; ++j){
			cin >> maze[i][j];
			grid[i][j] = 10000;
		}
		grid[0][0] = 1;

		queue<pair<int, int>> pos;

		pos.push(pair<int, int>(0, 0));

		while (pos.size())
		{
			int co = pos.front().first, ro = pos.front().second;
			pos.pop();
			if (maze[co][ro] == '+' && ro>=0 && co>=0)
			{
				if (grid[co + 1][ro] != min(grid[co + 1][ro], grid[co][ro] + 1))
				{
					grid[co + 1][ro] = min(grid[co + 1][ro], grid[co][ro] + 1);
					pos.push(pair<int, int>(co + 1, ro));
				}

				if (grid[co][ro + 1] != min(grid[co][ro + 1], grid[co][ro] + 1))
				{
					grid[co][ro + 1] = min(grid[co][ro + 1], grid[co][ro] + 1);
					pos.push(pair<int, int>(co, ro + 1));
				}

				if ((co >= 1) && grid[co - 1][ro] != min(grid[co - 1][ro], grid[co][ro] + 1))
				{
					grid[co - 1][ro] = min(grid[co - 1][ro], grid[co][ro] + 1);
					pos.push(pair<int, int>(co - 1, ro));
				}
				if ((ro >= 1) && grid[co][ro - 1] != min(grid[co][ro - 1], grid[co][ro] + 1))
				{
					grid[co][ro - 1] = min(grid[co][ro - 1], grid[co][ro] + 1);
					pos.push(pair<int, int>(co, ro - 1));
				}
			}
			else if (maze[co][ro] == '-')
			{
				if (grid[co][ro + 1] != min(grid[co][ro + 1], grid[co][ro] + 1))
				{
					grid[co][ro + 1] = min(grid[co][ro + 1], grid[co][ro] + 1);
					pos.push(pair<int, int>(co, ro + 1));
				}
				if ((ro >= 1) && grid[co][ro - 1] != min(grid[co][ro - 1], grid[co][ro] + 1))
				{
					grid[co][ro - 1] = min(grid[co][ro - 1], grid[co][ro] + 1);
					pos.push(pair<int, int>(co, ro - 1));
				}
			}
			else if (maze[co][ro] == '|' && ro >= 0 && co >= 0)
			{
				if (grid[co + 1][ro] != min(grid[co + 1][ro], grid[co][ro] + 1))
				{
					grid[co + 1][ro] = min(grid[co + 1][ro], grid[co][ro] + 1);
					pos.push(pair<int, int>(co + 1, ro));
				}
				if ((co >= 1) && grid[co - 1][ro] != min(grid[co - 1][ro], grid[co][ro] + 1))
				{
					grid[co - 1][ro] = min(grid[co - 1][ro], grid[co][ro] + 1);
					pos.push(pair<int, int>(co - 1, ro));
				}
			}

		}

		if (grid[row - 1][col - 1] == 10000)
		{
			cout << "-1" << endl;
		}
		else if (maze[row - 1][col - 1] == '*')
			cout << "-1" << endl;
		else
			cout << grid[row - 1][col - 1] << endl;
	}
	return 0;
}