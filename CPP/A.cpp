#include <bits/stdc++.h>

using namespace std;

vector<int> graph[200010];
int mdist[200010][3], to[200010][3], N;

void dfs(int v, int p){
	if (graph[v].size() == 1 && graph[v][0] == p){
		mdist[v][0] = 0;
	}
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
		mdist[v][2] = 1 + mdist[u][0];	
		to[v][2] = u;
		for (int i=1; i>=0; --i){
			if (mdist[v][i] < mdist[v][i+1]){
				swap(mdist[v][i], mdist[v][i+1]);
				swap(to[v][i], to[v][i+1]);
			}
		}
	}
	// cout < v << " " << mdist[v][0] << endl;
}

void dfs2(int v, int p, int d){
	mdist[v][2] = d;
	to[v][2] = p;
	for (int i=1; i>=0; --i){
		if (mdist[v][i] < mdist[v][i+1]){
			swap(mdist[v][i], mdist[v][i+1]);
			swap(to[v][i], to[v][i+1]);
		}
	}
	for (int u : graph[v]){
		if (u == p)
			continue;
		if (to[v][0] == u)
			dfs2(u, v, mdist[v][1] + 1);
		else
			dfs2(u, v, mdist[v][0] + 1);
	}
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<N-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	dfs(1, -1);
	dfs2(1, -1, 0);

	int v = 0, d = 1e9;
	for (int i=1; i<=N; ++i){
		if (mdist[i])
	}

	return 0;
}