#include <iostream>
#include <algorithm>

int board[9][9];

using namespace std;

int main()
{
	int p1[2], p2[2];
	cin >> p1[0] >> p1[1] >> p2[0] >> p2[1];
	int cm[8][2];
	cm[0][0] = 2, cm[0][1] = 1, cm[1][0] = 2, cm[1][1] = -1, cm[2][0] = -2, cm[2][1] = 1 , cm[3][0] = -2, cm[3][1] = -1;
	cm[4][0] = 1, cm[4][1] = 2, cm[5][0] = 1, cm[5][1] = -2, cm[6][0] = -1, cm[6][1] = 2 , cm[7][0] = -1, cm[7][1] = -2;

	//p1[0] = 4, p1[1] = 2, p2[0] = 7, p2[1] = 5;
	for (int i = 0; i != 9; ++i)
	for (int j = 0; j != 9; ++j)
		board[i][j] = 99;
	//board[4][2] = 0;
	for (int k = 0; k != 9; ++k)
	for (int i = 0; i != 9; ++i)
	for (int j = 0; j != 9; ++j)
	{
		for (int k = 0; k != 8; ++k)
		{
			if ((0<i + cm[k][0]) && (0<j + cm[k][1]) && (i + cm[k][0]<9) && (j + cm[k][1]<9))
				board[i][j] = min(board[i][j], board[i + cm[k][0]][j + cm[k][1]]);
		}
		board[i][j] += 1;
		board[p1[0]][p1[1]] = 0;
	}
	cout << board[p2[0]][p2[1]];
	return 0;
}