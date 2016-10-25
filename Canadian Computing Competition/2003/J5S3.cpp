#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int N, R, C;

int grid[26][26];
int rooms[577];

void flood(int r, int c, int val)
{
	if (grid[r][c] == 0 && r < R && c < C)
	{
		grid[r][c] = val;
		if (r >= 1)
			flood(r - 1, c, val);
		if (r < R - 1)
			flood(r + 1, c, val);
		if (c >= 1)
			flood(r , c - 1, val);
		if (c < C - 1)
			flood(r, c + 1, val);
	}
}



int main()
{
	//ifstream file("FloorPlan.txt");
	cin >> N >> R >> C;
	for (int j = 0; j != R; ++j)
	for (int i = 0; i != C; ++i)
	{
		char w;
		cin >> w;
		if (w == 'I')
			grid[j][i] = -1;
		else
			grid[j][i] = 0;
	}

	int val = 1;
	for (int j = 0; j != R; ++j)
	for (int i = 0; i != C; ++i)
	{
		if (grid[j][i] == 0)
		{
			flood(j, i, val);
			++val;
		}
	}
	for (int j = 0; j != R; ++j)
	for (int i = 0; i != C; ++i)
	{
		if (grid[j][i] != -1)
		{
			++rooms[grid[j][i]];
		}
	}
	sort(rooms, rooms + val);
	int croom = 0;
	for (int i = val - 1; i > 0 && N >= rooms[i]; --i)
	{
		N -= rooms[i];
		++croom;
	}
	if (croom == 1)
		cout << croom << " room, " << N << " square metre(s) left over" << endl;
	else
		cout << croom << " rooms, " << N << " square metre(s) left over" << endl;
	return 0;
}