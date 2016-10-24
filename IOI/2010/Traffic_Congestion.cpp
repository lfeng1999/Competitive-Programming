#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define rint(a) scanf("%d",&a)
const int MAXN = 1000010;
int congest[MAXN], fan[MAXN], N, ftot = 0;
bool past[MAXN];
vector<int> graph[MAXN];

int bash(int node)
{
	int temp = 0;
	past[node] = true;
	for (int i = 0; i != graph[node].size(); ++i)
	{
		if (!past[graph[node][i]])
		{
			int t = bash(graph[node][i]);
			congest[node] = max(congest[node], t);
			temp += t;
		}
	}
	congest[node] = max(congest[node], ftot - fan[node] - temp);
	return temp + fan[node];
}

int main()
{
	//freopen("TrafficCongest.txt","r",stdin);
	rint(N);
	for (int i = 0; i != N; ++i)
	{
		rint(fan[i]);
		ftot += fan[i];
	}
	for (int i = 0; i != N - 1; ++i)
	{
		int a, b;
		rint(a);
		rint(b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	bash(0);
	int mcongest = congest[0], city = 0;
	for (int i = 1; i != N; ++i)
	if (congest[i] < mcongest)
	{
		mcongest = congest[i];
		city = i;
	}
	cout << city;
	return 0;
}