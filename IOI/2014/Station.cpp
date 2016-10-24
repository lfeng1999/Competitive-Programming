#include <iostream>

int s[700001];

using namespace std;

int main()
{
	int n = 0, k = 0, p=0, d=0, pos=0;
	cin >> n >> k;
	for (int i = 0; i != n; ++i)
		cin >> s[i];
	while (p != n - 1)
	{
		int move = 0;
		for (int i = k; i != 0; --i)
		{
			if (s[p + i] == 1)
			{
				p += i;
				++d;
				move = 1;
				break;
			}
		}
		if (!move)
		{
			pos = 0;
			break;
		}
		if (p == n - 1)
			pos = 1;
	}
	if (pos)
		cout << d;
	else
		cout << -1;
	return 0;
}