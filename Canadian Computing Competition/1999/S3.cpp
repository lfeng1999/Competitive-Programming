#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int power(int n, int k)
{
	int total = 1;
	for (int i = 0; i != k; ++i)
		total *= n;
	return total;
}

int main()
{
	int d, n, b, t, l, r;
	cin >> d;
	for (int i = 0; i != d; ++i)
	{
		char grid[245][245];
		cin >> n >> b >> t >> l >> r;
		int gsize = power(3, n);
		for (int i = 1; i <= gsize; ++i)
		for (int j = 1; j <= gsize; ++j)
			grid[i][j] = '*';
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 0; j != i; ++j)
			{
				for (int k = 0; k != i; ++k)
				{
					int square = power(3, n - i);
					int nsquare = gsize / power(3, n - i + 1);
					for (int a = 0; a != nsquare; ++a)
					for (int b = 0; b != nsquare; ++b)
					{
						for (int x = square + 1 + a*square*3; x <= square * 2 + a*square*3; ++x)
						for (int y = square + 1 + b*square*3; y <= square * 2 + b*square*3; ++y)
							grid[x][y] = ' ';
					}

				}
			}
		}
		for (int i = t; i >= b; --i)
		{
			for (int j = l; j <= r; ++j)
				cout << grid[i][j] << " ";
			cout << endl;
		}
		cout << endl;


	}


	return 0;
}