#include <iostream>
#include <algorithm>

using namespace std;

bool win[31][31][31][31];
int N, a, b, c, d;
bool winpos(int ax, int bx, int cx, int dx)
{
	if (ax >= 0 && bx >= 0 && cx >= 0 && dx >= 0 && !win[ax][bx][cx][dx])
		return true;
	return false;
}


int main()
{
	int moves[5][4] = { { 2, 1, 0, 2 }, { 1, 1, 1, 1 }, { 0, 0, 2, 1 }, { 0, 3, 0, 0 }, { 1, 0, 0, 1 } };
	for (int i = 0; i != 9; ++i)
	for (int j = 0; j != 9; ++j)
	for (int k = 0; k != 9; ++k)
	for (int l = 0; l != 9; ++l)
	for (int m = 0; m != 5; ++m)
		if (winpos(i - moves[m][0], j - moves[m][1], k - moves[m][2], l - moves[m][3]))
			win[i][j][k][l] = true;

	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> a >> b >> c >> d;
		if (win[a][b][c][d])
			cout << "Patrick" << endl;
		else
			cout << "Roland" << endl;

	}
	return 0;
}