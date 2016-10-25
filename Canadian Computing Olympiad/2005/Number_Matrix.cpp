#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int R, C, a = 5, b = 6, c = 7;

int matrix[105][105];
bool ipassed[105][105];

bool valid(int row, int col)
{
	if (matrix[row][col] == a | matrix[row][col] == b | matrix[row][col] == c)
		return true;
	else
		return false;
}

void flood(int row, int col , bool passed[105][105])
{
	if (!passed[row][col] && (matrix[row][col] == a | matrix[row][col] == b | matrix[row][col] == c))
	{
		passed[row][col] = true;
		if (row == R - 1)
		{
			cout << min(a, min(b, c)) << " " << a + b + c - max(a, max(b, c)) - min(a, min(b, c)) << " " << max(a, max(b, c)) << endl;
			exit(0);
		}
		if (row < R - 1)
			flood(row + 1, col, passed);
		if (row > 0)
			flood(row - 1, col, passed);
		if (col > 0)
			flood(row, col - 1, passed);
		if (col < C - 1)
			flood(row, col + 1, passed);
	}
}

int main()
{
	for (int i = 0; i != R; ++i)
	for (int j = 0; j != C; ++j)
		ipassed[i][j] = false;
	//ifstream file("Matrix.txt");
	scanf("%d%d", &C, &R);
	for (int i = 0; i != R; ++i)
	for (int j = 0; j != C; ++j)
		scanf("%d", &matrix[i][j]);
	for (a = 0; a < 10; ++a)
	for (b = a ; b < 10; ++b)
	for (c = b; c < 10; ++c)
	{
		for (int i = 0; i != R; ++i)
		for (int j = 0; j != C; ++j)
			ipassed[i][j] = false;
		//cout << a << " " << b << " " << c << endl;
		for (int m = 0; m != C; ++m)
		{
			flood(0, m, ipassed);
		}
	}
	cout << -1 << " " << -1 << " " << -1 << endl;
	return 0;
}