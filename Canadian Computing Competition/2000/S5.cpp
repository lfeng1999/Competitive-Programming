#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

typedef pair<double, double> PDD;

vector<PDD> sheep;

bool out[1001];

int main()
{
	//ifstream file("SheepCoyote.txt");
	int N = 0;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		sheep.push_back(make_pair(x, y));
	}
	sort(sheep.begin(), sheep.end());
	for (int i = 0; i != N; ++i)
	{
		double L = 0, R = 1000;
		for (int j = 0; j != N; ++j)
		{
			if (i != j)
			{
				double mx = (sheep[i].first + sheep[j].first) / 2;
				double my = (sheep[i].second + sheep[j].second) / 2;
				if (sheep[i].first == sheep[j].first)
				{
					if (sheep[i].second > sheep[j].second)
						out[i] = true;
					else
						out[j] = true;
				}
				else
				{
					double slope = (sheep[i].second - sheep[j].second) / (sheep[i].first - sheep[j].first);
					double xcept = my*slope + mx;
					if (i < j)
						R = min(R, xcept);
					else
						L = max(L, xcept);
					if (L > R + 0.00000001)
						out[i] = true;
				}
			}
			if (out[i])
				break;
		}
	}

	for (int i = 0; i != N; ++i)
	{
		if (!out[i])
		{
			printf("The sheep at (%.2f, %.2f) might be eaten.\n", sheep[i].first, sheep[i].second);
		}
	}

	return 0;
}