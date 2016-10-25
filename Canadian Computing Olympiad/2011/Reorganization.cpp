#include <iostream>
#include <set>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, R[100010], rk;

int main()
{
	set<pair<int, int>> order;
	//freopen("Reorganization.txt", "r", stdin);
	scanf("%d", &n);
	scanf("%d", &rk);
	order.insert(make_pair(rk, 0));
	for (int qq = 1; qq != n; ++qq)
	{
		scanf("%d", &rk);
		pair<int, int> np = make_pair(rk, qq);
		set<pair<int,int>>::const_iterator it = order.upper_bound(np);
		if (it == order.begin())
		{
			cout << "NO";
			return 0;
		}
		--it;
		R[it->second]++;
		if (R[it->second] == 2)
			order.erase(it);
		order.insert(np);
	}
	cout << "YES";
	return 0;
}