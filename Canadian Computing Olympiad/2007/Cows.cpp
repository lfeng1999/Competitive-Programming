#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

int cross(PII O, PII A, PII B)  // cross product of two vectors
{
	// matrice with vectors
	return (A.first - O.first)* (B.second - O.second) - (B.first - O.first) * (A.second - O.second);
}

int determin(PII A, PII B) // shoelace theorem
{
	return A.first*B.second - A.second * B.first;
}

vector<PII> points;
vector<PII> upperhull;
vector<PII> lowerhull;
PII hull[10002];

int shoelace[10001];

int main()
{
	int N = 0;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		points.push_back(make_pair(x, y));
	}
	sort(points.begin(), points.end());

	for (int i = 0; i != N; ++i)
	{
		while ((lowerhull.size() >= 2) && cross(lowerhull[lowerhull.size() - 2], lowerhull[lowerhull.size() - 1], points[i]) <= 0)
			lowerhull.pop_back();
		lowerhull.push_back(points[i]);
	}
	lowerhull.pop_back();
	for (int i = N - 1; i >= 0; --i)
	{
		while ((upperhull.size() >= 2) && cross(upperhull[upperhull.size() - 2], upperhull[upperhull.size() - 1], points[i]) <= 0)
			upperhull.pop_back();
		upperhull.push_back(points[i]);
	}
	for (int i = 0; i != lowerhull.size(); ++i)
		hull[i] = lowerhull[i];
	for (int i = 0; i != upperhull.size(); ++i)
		hull[lowerhull.size() + i] = upperhull[i];
	int total = 0;
	int phull = lowerhull.size() + upperhull.size() - 1;
	for (int i = 0; i != phull ; ++i)
	{
		total += determin(hull[i], hull[i + 1]);
	}
	total /= 100;
	cout << total;


	return 0;
}