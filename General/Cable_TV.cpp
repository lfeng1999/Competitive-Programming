#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct triple
{
	int n, c, d;
	triple(int a1, int b1, int c1)
	{
		n = a1, c = b1, d = c1;
	}
};

class comp
{
public:
	bool operator() (const triple &a, const triple &b) const
	{
		return !(a.d < b.d | (a.d == b.d && a.c < b.c));
	}
};

const int MAXN = 102;
typedef pair<int, pair<int, int>> PIPII; // dangerous, cost, next node 
#define rint(a) scanf("%d",&a)
vector<triple> graph[MAXN];
int N, M, w, x, y, z, tnode = 0, ansc = 0, ansd = 0;
bool passed[MAXN];

int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 0; i != M; ++i)
	{
		scanf("%d%d%d%d", &w, &x, &y, &z);
		graph[w].push_back(triple(x, y, z));
		graph[x].push_back(triple(w, y, z));
	}
	priority_queue<triple, vector<triple>, comp> Q;
	Q.push(triple(1, 0, 0)); //node, cost, dangerous
	while (!Q.empty() && tnode != N)
	{
		int node = Q.top().n, cost = Q.top().c, dan = Q.top().d; 
		Q.pop();
		if (passed[node])
			continue;
		passed[node] = true;
		ansc += cost;
		ansd += dan;
		tnode++;
		for (int i = 0; i != graph[node].size(); ++i)
		{
			int newnode = graph[node][i].n;
			if (!passed[newnode])
			{
				Q.push(graph[node][i]);
			}
		}
	}
	cout << ansd << " " << ansc;
	return 0;
}