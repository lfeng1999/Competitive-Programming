#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

set<vector<int>> flakes;


int leg = 0, N = 0;

int main()
{
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		vector<int> snow;
		for (int k = 0; k != 6; ++k)
		{
			scanf("%d", &leg);
			snow.push_back(leg);
		}
		sort(snow.begin(), snow.end());
		if (!flakes.insert(snow).second)
		{
			cout << "Twin snowflakes found.";
			exit(0);
		}
	}
	cout << "No two snowflakes are alike.";
	return 0;
}