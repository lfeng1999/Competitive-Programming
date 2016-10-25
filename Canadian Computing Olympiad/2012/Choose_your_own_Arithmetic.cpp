#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int> ans[7];
int dig[7];
int W, D, V, vans;

void bash(int n, int m)
{
	if (!ans[m].insert(n).second | m == 0)
		return;
	for (int i = 0; i != D; ++i)
	{
		bash(n + dig[i], m - 1);
		bash(n * dig[i], m - 1);
	}
}

int main()
{
	cin >> W >> D;
	for (int i = 0; i != D; ++i)
		cin >> dig[i];
	for (int i = 0; i != D; ++i)
		bash(dig[i], W);
	cin >> V;
	for (int i = 0; i != V; ++i)
	{
		cin >> vans;
		if (!ans[0].insert(vans).second)
			cout << "Y" << endl;
		else
			cout << "N" << endl;
	}
	return 0;
}