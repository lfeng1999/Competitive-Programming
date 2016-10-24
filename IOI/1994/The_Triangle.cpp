#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int size = 5;
	int tri[100][100];
	cin >> size;
	for (int x = 0; x < size; ++x)
	{
		for (int i = 0; i <= x; ++i) {
			cin >> tri[x][i];
		}
	}

	for (int i = 1; i < size;++i)
	for (int j = 0; j < size - i; ++j)
		tri[size - 1 - i][j] += max(tri[size - i][j], tri[size - i][j + 1]);

	cout << tri[0][0];

	return 0;
}
