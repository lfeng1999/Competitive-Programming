#include <iostream>
#include <algorithm>

int sens[2000001];
int times[1001];

using namespace std;

int main()
{
	int N = 0;
	cin >> N;
	for (int i = 0; i != N; ++i)
		cin >> sens[i];
	for (int i = 1; i != 1001; ++i)
		times[i] = count(sens, sens+N, i);

	int s1 = 0, s2 = 0, high = 0, high2 = 0,dist=0;

	for (int i = 0; i != 1001; ++i)
	{
		if (times[i] >= high)
		{
			high2 = high;
			high = times[i];
		}
		else if (times[i] <= high)
		{
			high2 = max(high2,times[i]);
		}
	}
	for (int i = 0; i != 1001; ++i)
	{
		if (times[i] == high)
		{
			s1 = i;
		}
	}
	for (int i = 1; i != 1001; ++i)
	{
		if (times[i] == high2)
		{
			s2 = i;
			dist = max(dist, abs(s1 - s2));
		}
	}
	cout << dist;
	return 0;
}