#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

#define INF 0x7fffffff
#define INF2 0x0fffffff

int N, c[4];

int eval(int a, int func, int b)
{
	if (func == 0)
		return a + b;
	else if (func == 1)
		return a - b;
	else if (func == 2)
		return a*b;
	else if (func == 3 && b!=0 && a%b == 0)
		return a / b;
	return -INF2;
}

int main()
{
	cin >> N;
	for (int a = 0; a != N; ++a)
	{
		for (int j = 0; j != 4; ++j)
			cin >> c[j];
		sort(c, c + 4);
		int maxn = 0;
		do
		{
			for (int i = 0; i != 4; ++i)
			for (int j = 0; j != 4; ++j)
			for (int k = 0; k != 4; ++k)
			{
				int n[2];
				n[0] = eval(eval(eval(c[0], i, c[1]), j, c[2]), k, c[3]);   //((a+b)+c)+d
				n[1] = eval(eval(c[0], i, c[1]), j, eval(c[2], k, c[3]));   //((a+b)+(c+d))
				for (int b = 0; b != 2; ++b)
				{
					if (n[b] <= 24 && maxn < n[b])
						maxn = n[b];
				}
			}
			if (maxn == 24)
				break;
		} while (next_permutation(c, c + 4));
		cout << maxn << endl;
	}
	return 0;
}