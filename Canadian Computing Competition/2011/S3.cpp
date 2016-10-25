#include <iostream>
#include <algorithm>

using namespace std;



int alice(int magnif,int x, int y,int stal[4][2])
{
	int fBool = 0;
	int x1 = 0, y1 = 0;
	x1 = x / pow(5, magnif-1);
	y1 = y / pow(5, magnif-1);
	if (x1 == 2 && y1 == 0)
		fBool = 1;
	for (int i = 0; i < 3; ++i)
	{
		if (x1 == stal[i][0] && y1 == stal[i][1])
		{
			fBool = 1;
			break;
		}
	}
	if (fBool==0)
	{
		if (magnif != 1)
		{
			for (int i = 0; i < 3; ++i)
			{
				fBool = alice(magnif - 1, x - stal[i][0] * pow(5, magnif - 1), y - (stal[i][1]+1) * pow(5, magnif - 1), stal);
				if (fBool)
					break;
			}
		}
		else
			fBool=0;
	}
	return fBool;
}






int main()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int crystals[4][2];
	crystals[0][0] = 1;
	crystals[0][1] = 0;
	crystals[1][0] = 3;
	crystals[1][1] = 0;
	crystals[2][0] = 2;
	crystals[2][1] = 1;
	int num=4;
	cin >> num;
	int crys[10][3];
	for (int i = 0; i < num; ++i)
	for (int j = 0; j < 3; ++j)
		cin >> crys[i][j];
	for (int i = 0; i < num; ++i)
	{
		if (alice(crys[i][0], crys[i][1], crys[i][2], crystals))
			cout << "crystal" << endl;
		else
			cout << "empty" <<  endl;
	}
	return 0;
}