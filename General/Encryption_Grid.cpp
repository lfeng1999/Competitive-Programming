#include <iostream>
#include <string>

using namespace std;

int main()
{
	int length = 0;
	cin >> length;
	while (length != 0)
	{
		string grid;
		cin >> grid;
		for (int j = 0; j != length; ++j)
		for (int i = 0; i != grid.length() / length; ++i)
		{
			if (!(i%2))
				cout << grid[i * length + j];
			else
				cout << grid[(i+1) * length - j-1];

		}
		cout << endl;
		cin >> length;
	}
	return 0;
}