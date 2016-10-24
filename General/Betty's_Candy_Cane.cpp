#include <iostream>
#include <algorithm>

int board[10][10];

using namespace std;

int main()
{
	int p[2];
	cin >> p[0] >> p[1];
	int cm[8][2];
	cm[0][0] = -1, cm[0][1] = 0, cm[1][0] = 1, cm[1][1] = 0, cm[2][0] = 0, cm[2][1] = 1, cm[3][0] = 0, cm[3][1] = -1;

	//p1[0] = 4, p1[1] = 2, p2[0] = 7, p2[1] = 5;
	for (int i = 0; i != 10; ++i)
	for (int j = 0; j != 10; ++j)
		board[i][j] = 1000;

	//bombs

	board[0][3] = 1800;
	board[2][2] = 1800;
	board[6][1] = 1800;
	board[9][0] = 1800;
	board[8][2] = 1800;
	board[9][9] = 1800;
	board[7][8] = 1800;
	board[7][6] = 1800;
	board[3][8] = 1800;
	board[1][7] = 1800;
	board[0][5] = 1800;
	board[1][5] = 1800;
	board[2][5] = 1800;
	board[3][5] = 1800;
	board[4][5] = 1800;
	board[5][5] = 1800;
	board[6][5] = 1800;


	//board[4][2] = 0;
	board[0][0] = 0;
	int past = 0;
	for (int k = 0; k != 15; ++k)
	for (int i = 0; i != 10; ++i)
	for (int j = 0; j != 10; ++j)
	{
		if (board[i][j] != 1800)
		{
			past = board[i][j];
			for (int k = 0; k != 4; ++k)
			{
				if ((0 <= i + cm[k][0]) && (0 <= j + cm[k][1]) && (i + cm[k][0] < 10) && (j + cm[k][1] < 10))
					board[i][j] = min(board[i][j], board[i + cm[k][0]][j + cm[k][1]]);
			}
			if (past != board[i][j])
				board[i][j] += 1;
		}
	}
	//for (int i = 0; i != 10; ++i)
	//{
	//	for (int j = 0; j != 10; ++j)
	//	{
	//		if (board[i][j] == 1800)
	//			cout << "X ";
	//		else
	//			cout << board[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cout << "Betty will sweat " << board[p[0]-1][p[1]-1] << "mL to get to her candy cane";
	return 0;
}