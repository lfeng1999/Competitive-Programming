#include <iostream>
#include <algorithm>

using namespace std;
int olives[4001], size[4001], vals[150001];

int main()
{
	int Q, M, K;
	scanf("%d%d%d", &Q, &M, &K);
	for (int i = 0; i != M; ++i)
	{
		scanf("%d", &olives[i]);
		size[i] = olives[i];
		vals[size[i]] = min(vals[size[i]], olives[i]);
	}
	for (int i = M; i != M + K; ++i)
	{
		scanf("%d", &size[i]);
		olives[i] = size[i] - 1;
		vals[size[i]] = min(vals[size[i]], olives[i]);
	}
	int molive = 0;
	for (int j = 0; j != M + K; ++j)
	for (int i = Q; i >= 0; --i)
	{
		if (i + size[j] > Q)
		{
			vals[Q] = max(vals[Q], vals[i] + Q - i - 1);
			molive = max(molive, vals[Q]);
		}
		else
		{
			vals[i + size[j]] = max(vals[i + size[j]], vals[i] + olives[j]);
			molive = max(molive, vals[i + size[j]]);
		}
	}

	cout << molive;
	return 0;
}