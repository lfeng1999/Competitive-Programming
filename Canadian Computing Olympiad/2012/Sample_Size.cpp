#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	int N = 0, len=0;
	set<int> per;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		int P = 0;
		cin >> P;
		per.insert(per.end(), P);
	}
	set<int>::const_iterator iter;
	for (iter = per.begin(); iter != per.end(); ++iter)
		++len;
	int tlen = 0;
	int temp = 0;
	for (double i = 1; i <= 100; ++i)
	{
		tlen = 0;
		for (double j = 1; j <= i; ++j)
		{
			for (iter = per.begin(); iter != per.end(); ++iter)
			{
				temp = round(j * 100 / i);
				if (temp == *iter)
				{
					tlen++;
				}
			}
		}
		if (tlen == len)
		{
			cout << i;
			break;
		}
	}
	if (tlen != len)
	{
		cout << 1;
	}
	return 0;
}