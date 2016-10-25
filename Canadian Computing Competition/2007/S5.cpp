#include <iostream>
#include <vector>
#include <algorithm>

int pins[30001];
int p[30001];
int sum[30001][501];

using namespace std;

int main()
{
	int t = 1, n = 9, k = 2, w = 3, maxi = 0;
	cin >> t;
	for (int num = 0; num != t; ++num)
	{
		cin >> n >> k >> w;
		maxi = 0;
		for (int i = 0; i < n; ++i)
			cin >> pins[i];
		for (int j = 0; j < n - w + 1; ++j)
		{
			for (int cnt = 0; cnt < w; ++cnt)
				p[j] += pins[j + cnt];
		}
		for (int j = 0; j != k; ++j)
		for (int i = 0; i != n; ++i)
		{
			if (i - w >= 0)
				sum[i][j] = max(sum[i - w][j - 1] + p[i], sum[i - 1][j]);
			else if (i>0)
				sum[i][j] = max(p[i], sum[i - 1][j]);
			else
				sum[i][j] = p[i];
			maxi = max(maxi, sum[i][j]);
		}
		cout << maxi << endl;
		if (num != t - 1)
		{
			for (int i = 0; i != 30001; ++i)
			{
				p[i] = 0;
				for (int j = 0; j != 501; ++j)
					sum[i][j] = 0;
			}
		}
	}
	return 0;
}