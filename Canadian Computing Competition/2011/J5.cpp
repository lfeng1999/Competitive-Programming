#include <iostream>

using namespace std;

int main()
{
	int N=6;
	int vited[5];
	cin >> N;
	for (int i = 0; i < N-1; ++i)
		cin >> vited[i];
	int table[6][6];
	
	int count[6];
	for (int i = 0; i < 6; ++i)
		count[i] = 0;
	for (int i = 0; i < 6; ++i)
	for (int j = 0; j < 6; ++j)
		table[i][j] = 0;
	for (int i = 0; i < N - 1; ++i)
	{
		table[count[vited[i] - 1]][vited[i] - 1] = i + 1;
		count[vited[i] - 1]++;
	}

	int col[7];
	col[0] = 0;
	for (int i = 1; i < 7; ++i)
		col[i] = 1;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			col[i + 1] = col[i + 1] * (col[table[j][i]] + 1);
		}
	}
	cout << col[N];
	return 0;
}