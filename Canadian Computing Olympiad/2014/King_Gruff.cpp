#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#define maxn 100010
#define rint(a) scanf("%d",&a)
#define rint2(a,b) scanf("%d%d",&a,&b)
#define rchar(a) scanf(" %c", &a)

int dist1[2][maxn];
vector<pair<int, int>> costs;



struct Edge
{
	int city, dist, cost;
	Edge(int destination, int distance, int shutdown)
	{
		city = destination;
		dist = distance;
		cost = shutdown;
	}
};

vector<Edge> edges[2][maxn];

int prefix[100010];

int binsearch(int value, int first, int last)
{
	if (first + 1 == last)
		return first;
	int mid = (first + last) / 2;
	if (costs[mid].first > value)
		return binsearch(value, first, mid);
	return binsearch(value, mid, last);

}

void djikstra(int A, int ver)
{
	bool inq[maxn];
	for (int i = 0; i != maxn; ++i)
		inq[i] = false;
	queue<int> place;
	place.push(A);
	inq[A] = true;
	while (!place.empty())
	{
		int top = place.front();
		place.pop();
		inq[top] = false;
		for (int i = 0; i != edges[ver][top].size(); ++i)
		{
			if (dist1[ver][top] + edges[ver][top][i].dist < dist1[ver][edges[ver][top][i].city])
			{
				dist1[ver][edges[ver][top][i].city] = dist1[ver][top] + edges[ver][top][i].dist;
				if (!inq[edges[ver][top][i].city])
				{

					place.push(edges[ver][top][i].city);
					inq[edges[ver][top][i].city] = true;
				}
			}
		}
	}
}


int main()
{
	for (int i = 0; i != 2; ++i)
	{
		for (int j = 0; j != maxn; ++j)
		{
			dist1[i][j] = 999999999;
		}
	}

	int N = 0, M = 0, A = 0, B = 0;
	scanf("%d%d%d%d", &N, &M, &A, &B);
	
	for (int i = 0; i != M; ++i)
	{
		int X = 0, Y = 0, L = 0, C = 0;
		//cin >> X >> Y >> L >> C;
		scanf("%d%d%d%d", &X, &Y, &L, &C);
		edges[0][X].push_back(Edge(Y, L, C));
		edges[1][Y].push_back(Edge(X, L, C));
	}
	int Q = 0;
	scanf("%d", &Q);
	
	dist1[0][A] = 0;
	dist1[1][B] = 0;


	djikstra(A, 0);
	djikstra(B, 1);

	for (int i = 1; i <= N; ++i)
	for (int j = 0; j != edges[0][i].size(); ++j)
	{
		costs.push_back(make_pair(dist1[0][i] + edges[0][i][j].dist + dist1[1][edges[0][i][j].city], edges[0][i][j].cost));
	}
	sort(costs.begin(), costs.end());
	costs.push_back(make_pair(99999999, 0));
	int total = 0;
	for (int i = 0; i != costs.size(); ++i)
	{
		total += costs[i].second;
		prefix[i] = total;
	}
	for (int k = 0; k != Q; ++k)
	{
		int mdist = 0;
		scanf("%d", &mdist);
		int counter = 0;

		counter = binsearch(mdist, 0, costs.size() - 1);

		if (counter >= 0)
			printf("%d\n", prefix[counter]);
		else
			puts("0");
	}


	return 0;
}