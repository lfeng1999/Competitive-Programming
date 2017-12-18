#include <bits/stdc++.h>

using namespace std;

vector<int> graph[500010];
int dist[500010][3], to[500010][3], N;

void dfs(int v, int p){
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
		dist[v][2] = dist[u][0] + 1;
		to[v][2] = u;
		for (int i=2; i>0; --i){
			if (dist[v][i] > dist[v][i-1]){
				swap(dist[v][i], dist[v][i-1]);
				swap(to[v][i], to[v][i-1]);
			}
		}
	}
}

int dfs2(int v, int p){
	for (int u : graph[v]){
		if (u == p) continue;
		if (to[v][0] == u){
			dist[u][2] = dist[v][1] + 1;
			to[u][2] = v;
		}
		else{
			dist[u][2] = dist[v][0] + 1;
			to[u][2] = v;
		}
		for (int i=2; i>0; --i){
			if (dist[u][i] > dist[u][i-1]){
				swap(dist[u][i], dist[u][i-1]);
				swap(to[u][i], to[u][i-1]);
			}
		}
		dfs2(u, v);
	}
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N;
	for (int i=0; i<N-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}

	dfs(1, -1);
	dfs2(1, -1);
	for (int i=1; i<=N; ++i){
		cout << dist[i][0] + 1 << '\n';
	}


	return 0;
}