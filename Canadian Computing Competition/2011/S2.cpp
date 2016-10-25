#include <iostream>

char sub[10000];
char ans[10000];

using namespace std;


int main()
{
	int count=3;
	int point = 0;
	cin >> count;
	for (int i = 0; i < count; ++i)
		cin >> sub[i];
	for (int i = 0; i < count; ++i)
		cin >> ans[i];
	for (int i = 0; i < count; ++i)
	{
		if (sub[i] == ans[i])
			point++;
	}
	cout << point;
	return 0;
}