#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

int N, W, P, comp[101][101], c1, c2, t;

int main()
{
	//ifstream file("Routing.txt");
	cin >> N >> W >> P;
	for (int i = 0; i != W; ++i)
	{
		cin >> c1 >> c2 >> t;
		comp[c1][c2] = comp[c2][c1] = t;
	}
	for (int i = 1; i <= N; ++i)
	for (int j = 1; j <= N; ++j)
	{
		if (comp[i][j])
		{
			for (int k = 1; k <= N; ++k)
			if (comp[j][k] && (comp[i][k]==0 | comp[i][k] > comp[i][j]+comp[j][k]))
				comp[i][k] = comp[k][i] = comp[i][j] + comp[j][k];
		}	
	}
	for (int i = 0; i != P; ++i)
	{
		cin >> c1 >> c2;
		cout << comp[c1][c2] << endl;
	}
	return 0;
}