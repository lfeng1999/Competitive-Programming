#include <bits/stdc++.h>

using namespace std;

int md[300010][4], par[300010], nv[300010][4], N, bd[300010], rbd[300010], child[300010];
vector<int> graph[300010];

void dfs(int v, int p){
	for (int u : graph[v]){
		if (u == p)
			continue;
		dfs(u, v);
		md[v][3] = md[u][0] + 1;
		nv[v][3] = u;
		for (int i=2; i>=0; --i){
			if (md[v][i] < md[v][i+1]){
				swap(md[v][i], md[v][i+1]);
				swap(nv[v][i], nv[v][i+1]);
			}
		}
	}
}
void dfs2(int v, int p, int d){
	md[v][3] = d;
	nv[v][3] = p;
	for (int i=2; i>=0; --i){
		if (md[v][i] < md[v][i+1]){
			swap(md[v][i], md[v][i+1]);
			swap(nv[v][i], nv[v][i+1]);
		}
	}
	for (int u : graph[v]){
		if (u == p)
			continue;
		if (nv[v][0] == u)
			dfs2(u, v, md[v][1] + 1);
		else
			dfs2(u, v, md[v][0] + 1);
	}
}
bool past[300010];
int furthest(int v){
	memset(past, false, sizeof(past));
	queue<int> Q;
	Q.push(v);
	past[v] = true;
	par[v] = -1;

	while (!Q.empty()){
		v = Q.front();
		Q.pop();
		for (int u : graph[v]){
			if (past[u])
				continue;
			par[u] = v;
			past[u] = true;
			Q.push(u);
		}
	}
	return v;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<N-1; ++i){
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	dfs(1, -1);
	dfs2(1, -1, 0);
	int v = 1;
	v = furthest(v);
	v = furthest(v);
	int ov = v;
	int ans = 1e9;
	child[v] = -1;
	while (par[v] != -1){
		int u = par[v];
		if (u == nv[v][0]){
			bd[v] = max(bd[v], md[v][1] + md[v][2]);
		}
		else if (u == nv[v][1]){
			bd[v] = max(bd[v], md[v][0] + md[v][2]);
		}
		else{
			bd[v] = max(bd[v], md[v][0] + md[v][1]);
		}
		bd[par[v]] = bd[v];
		child[par[v]] = v;
		v = par[v];
	}
	while (child[v] != -1){
		int u = child[v];
		if (u == nv[v][0]){
			rbd[v] = max(rbd[v], md[v][1] + md[v][2]);
		}
		else if (u == nv[v][1]){
			rbd[v] = max(rbd[v], md[v][0] + md[v][2]);
		}
		else{
			rbd[v] = max(rbd[v], md[v][0] + md[v][1]);
		}
		rbd[child[v]] = rbd[v];

		v = child[v];
	}


	while (par[v] != -1){
		int u = par[v];
		// cout << bd[v] << " " << rbd[u] << endl;
		int md1 = (bd[v] + 1)/2;
		int md2 = (rbd[u] + 1)/2;
		ans = min(ans, max(1 + md1 + md2, max(bd[v], rbd[u])));
		v = par[v];
	}
	cout << ans;
	return 0;
}