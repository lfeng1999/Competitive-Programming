#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define INF 100000000

int dists[201], n, k;


int works(int len)
{
	int pos = 0;
	int total = 0;
	while (pos != n)
	{
		for (int i = pos; i <= n; ++i)
		if (dists[pos] + len < dists[i])
		{
			pos = i - 1;
			break;
		}
		for (int i = pos; i <= n; ++i)
		if (dists[pos] + len < dists[i])
		{
			pos = i;
			break;
		}
		++total;
	}
	return total;
}
void works2(int len)
{
	int pos = 0;
	int total = 0;
	while (pos != n)
	{
		for (int i = pos; i <= n; ++i)
		if (dists[pos] + len < dists[i])
		{
			pos = i - 1;
			break;
		}
		cout << dists[pos] << " ";
		for (int i = pos; i <= n; ++i)
		if (dists[pos] + len < dists[i])
		{
			pos = i;
			break;
		}
		++total;
	}
	if (total < k)
		cout << dists[n - 1];
}

int main()
{
	//ifstream file("FastFood.txt");
	cin >> n;
	while (n != 0)
	{
		for (int i = 0; i != 201; ++i)
			dists[i] = INF;
		cin >> k;
		for (int i = 0; i != n; ++i)
			cin >> dists[i];
		sort(dists, dists + n);
		int L = 0, R = 1000000;
		while (L != R)
		{
			int mid = (L + R) / 2;
			if (works(mid) <= k)
				R = mid;
			else
				L = mid + 1;
		}
		works2(L);
		cout << endl << L << endl << endl;
		cin >> n;
	}

	return 0;
}