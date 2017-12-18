#include <bits/stdc++.h>

using namespace std;

struct Edge{
	int v, u, d;
} edges[30010];

struct Edge2{
	int u, d, i;
};

vector<Edge2> graph[1010];

int N, M, src, snk;
int idx[1010], pre[1010];
bool seen[1010];
vector<int> curans;

int root[1010], pre2[1010], idx2[1010], par[10][1010], dep[1010], ap[1010];

int find(int v){
	if (v == root[v]) return v;
	return root[v] = find(root[v]);
}

bool merge(int v, int u){ //logn path compression
	v = find(v), u = find(u);
	if (v == u) return false;
	root[v] = u;
	return true;
}

void dfs(int v, int p){
	par[0][v] = p;
	for (int i=1; i<10; ++i)
		par[i][v] = par[i-1][par[i-1][v]];
	pre2[v] = p;
	dep[v] = dep[p] + 1;
	for (auto &it : graph[v]){
		int u = it.u, d = it.d, i = it.i;
		if (u == p) continue;
		dfs(u, v);
		idx2[u] = i;
	}
}
bool used[30010];

int lca(int v, int u){
	if (dep[v] < dep[u]) swap(v, u);
	for (int i=9; i>=0; --i){
		if ((1 << i) <= dep[v] - dep[u]){
			v = par[i][v];
		}
	}
	if (v == u) return v;
	for (int i=9; i>=0; --i){
		if (par[i][v] != par[i][u]){
			v = par[i][v], u = par[i][u];
		}
	}
	return par[0][v];
}

void dfs2(int v, int p){
	for (auto &it : graph[v]){
		int u = it.u;
		if (u == p) continue;
		dfs2(u, v);
		ap[v] += ap[u];
	}
}


long long solve(int rem){
	for (int i=0; i<1010; ++i){
		root[i] = i; seen[i] = false; dep[i] = 0;
		graph[i].clear();
		ap[i] = 0;
	}
	for (int i=0; i<30010; ++i)
		used[i] = false;
	for (int i=0; i<M; ++i){
		if (i == rem) continue;
		int v = edges[i].v, u = edges[i].u, d = edges[i].d;
		if (merge(v, u)){
			used[i] = true;
			graph[v].push_back({u, d, i});
			graph[u].push_back({v, d, i});
		}
	}
	if (find(src) != find(snk)) return 0;
	dfs(src, src);
	for (int i=0; i<M; ++i){
		int v = edges[i].v, u = edges[i].u, d = edges[i].d;
		if (find(v) != find(src) || i == rem || used[i]) continue;
		int w = lca(v, u);
		ap[v]++; ap[u]++; ap[w] -= 2;
	}
	dfs2(src, src);
	long long ret = 1e18;
	curans.push_back(0);
	int curv = snk;
	while (curv != src){
		int i = curv;
		if (ap[i] == 0){
			if (edges[idx2[i]].d < ret){
				curans.pop_back();
				ret = edges[idx2[i]].d;
				curans.push_back(idx2[i]);
			}
		}
		curv = par[0][curv];
	}
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	cin >> src >> snk;
	for (int i=0; i<M; ++i){
		int v, u, d; cin >> v >> u >> d;
		graph[v].push_back({u, d, i});
		graph[u].push_back({v, d, i});
		edges[i] = (Edge){v, u, d};
	}
	queue<int> Q;
	Q.push(src);
	seen[src] = true;
	while (!Q.empty()){
		int v = Q.front();
		Q.pop();
		for (auto &it : graph[v]){
			int u = it.u, i = it.i, d = it.d;
			if (seen[u]) continue;
			seen[u] = true;
			idx[u] = i;
			pre[u] = v;
			Q.push(u);
		}
	}
	if (!seen[snk]){
		cout << 0 << '\n' << 0;
		return 0;
	}
	long long ans = 1e18;
	vector<int> bans;
	int endx = snk;
	while (endx != src){
		curans.clear();
		curans.push_back(idx[endx]);
		long long y = edges[idx[endx]].d + solve(idx[endx]); //edge to remove
		if (y < ans){
			ans = y;
			bans = curans;
		}
		endx = pre[endx];
	}
	if (ans >= 1e18){
		cout << -1;
	}
	else{
		cout << ans << '\n' << bans.size() << '\n';
		for (int x : bans) cout << x+1 << " ";
	}

	return 0;
}