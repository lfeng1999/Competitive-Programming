#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

int N, a, b, locat[51];
vector<pair<int, int>> stores;
double tot = 0;

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int main()
{
	//freopen("Fast Food.txt", "r", stdin);
	scanf("%d", &N);
	while (N != 0){
		memset(locat, 0, sizeof(locat));
		for (int i = 0; i != N; ++i)
		{
			scanf("%d%d", &a, &b);
			stores.push_back(make_pair(a, b));
		}
		for (double x = 0.005; x < 10; x += 0.01)
		{
			for (double y = 0.005; y < 10; y += 0.01)
			{
				double mdist = dist(x, y, stores[0].first, stores[0].second);
				int loc = 0;
				for (int i = 1; i != N; ++i)
				{
					double ndist = dist(x, y, stores[i].first, stores[i].second);
					if (ndist < mdist)
					{
						mdist = ndist;
						loc = i;
					}
				}
				locat[loc]++;
			}
		}
		for (int i = 0; i != N; ++i)
		{
			int x = (locat[i] + 5000) / 10000;
			cout << "Restaurant at ("<<stores[i].first <<"," << stores[i].second << ") serves " << x << "% of the population.\n";
		}
		printf("\n");
		scanf("%d", &N);
	}
	return 0;
}