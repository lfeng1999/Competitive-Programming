#include <iostream>

using namespace std;

bool hole[500][250];



//http://wcipeg.com/problem/ccc11j4

int main()
{
	int x = 250, y = 1;
	hole[x][1] = true;
	hole[x][2] = true;
	hole[x][3] = true;
	hole[x+1][3] = true;
	hole[x+2][3] = true;
	hole[x+3][3] = true;
	hole[x+3][4] = true;
	hole[x+3][5] = true;
	hole[x+4][5] = true;
	hole[x+5][5] = true;
	hole[x+5][4] = true;
	hole[x+5][3] = true;
	hole[x+6][3] = true;
	hole[x + 7][3] = true;
	hole[x + 7][4] = true;
	hole[x + 7][5] = true;
	hole[x + 7][6] = true;
	hole[x + 7][7] = true;
	hole[x + 6][7] = true;
	hole[x + 5][7] = true;
	hole[x + 4][7] = true;
	hole[x + 3][7] = true;
	hole[x + 2][7] = true;
	hole[x + 1][7] = true;
	hole[x][7] = true;
	hole[x - 1][7] = true;
	hole[x - 1][6] = true;
	hole[x - 1][5] = true;

	y = 5;
	x -= 1;

	char dirs[1000];
	int diss[1000];
	cin >> dirs[0] >> diss[0];
	int st = 0;
	while (dirs[st] != 'q')
	{
		++st;
		cin >> dirs[st] >> diss[st];
	}



	char dir = dirs[0];
	int dis = diss[0];

	char quit = 'n';



	for (int j = 0; j != st; ++j)
	{
		for (int i = 0; i != dis; ++i)
		{
			if (dir == 'u')
				--y;
			else if (dir == 'd')
				++y;
			else if (dir == 'r')
				++x;
			else if (dir == 'l')
				--x;
			if (hole[x][y])
				quit = 'y';
			hole[x][y] = true;
		}
		if (quit == 'y')
		{
			cout << x-250 << " -" << y << " " << "DANGER" << endl;
			break;
		}
		else
			cout << x-250 << " -" << y << " " << "safe" << endl;
		dir = dirs[j + 1];
		dis = diss[j + 1];
	}

	return 0;
}