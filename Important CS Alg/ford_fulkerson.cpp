/*
# of Edge Disjoint Path is the max flow of a graph with the edge weights all 1 (COOL RIGHT!?!?)
# of Node Disjoint Path is the max flow of a graph where the nodes are considered an edge with weights 1
e.g) node "v" is an edge from 100000+2*v <-> 100000+2*v+1 with weight of 1
Did not test this yet!!!
*/
#include <bits/stdc++.h>

using namespace std;

int g[110][110], src = 1, snk = 100, n;
bool past[110];
int dfs(int v, int p, int minpath){
	if (v == snk) return minpath;
	past[v] = true;
	for (int u=1; u<=n; ++u){
		if (g[v][u] > 0 && !past[u]){
			int flow = dfs(u, v, min(minpath, g[v][u]));
			if (flow > 0){
				g[v][u] -= flow;
				g[u][v] += flow;
				return flow;
			}
		}
	}
	return 0;
}

int max_flow(){
	int flow = 0, toadd = 0;
	while (toadd){
		memset(past, false, sizeof(past));
		toadd = dfs(src, -1, 1e9);
		flow += toadd;
	}
	return flow;
}



int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	return 0;
}