#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> graph[50010];
int root[50010], N, M, rnk[50010], par[17][50010], mst = 0, maxedge[17][50010], depth[50010];

int find(int v){
	if (root[v] == v)
		return v;
	return root[v] = find(root[v]);
}

bool merge(int v, int u, int d){
	v = find(v);
	u = find(u);
	if (root[v] == root[u])
		return false;
	if (rnk[v] < rnk[u])
		swap(v, u);
	root[u] = v;
	if (rnk[v] == rnk[u])
		rnk[v]++;
	return true;
}

void dfs(int v, int p, int d){
	if (p == -1)
		depth[v] = 1;
	else
		depth[v] = depth[p] + 1;
	par[0][v] = p;
	maxedge[0][v] = d;
	for (pair<int, int> E : graph[v]){
		int u = E.first, d = E.second;
		if (u == p) continue;
		dfs(u, v, d);
	}
}

int findmax(int v, int u){
	if (depth[v] < depth[u])
		swap(v, u);
	int diff = depth[v] - depth[u], ret = -1;
	// cout << diff << endl;
	for (int i=16; i>=0; --i){
		if (diff >= (1 << i)){
			diff -= (1 << i);
			ret = max(ret, maxedge[i][v]);
			v = par[i][v];
		}
	}
	// cout << v << " " << u << endl;
	if (v == u)
		return ret;
	for (int i=16; i>=0; --i){
		if (par[i][v] != par[i][u]){
			ret = max(ret, max(maxedge[i][v], maxedge[i][u]));
			v = par[i][v];
			u = par[i][u];
		}
	}
	ret = max(ret, max(maxedge[0][v], maxedge[0][u]));
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	vector<pair<int,pair<int,int>>> V;
	for (int i=1; i<=M; ++i){
		int v, u, d;
		cin >> v >> u >> d;
		V.push_back(make_pair(d, make_pair(v, u)));
	}
	for (int i=1; i<=N; ++i){
		root[i] = i;
		for (int j=0; j<17; ++j){
			par[j][i] = maxedge[j][i] = -1;
		}
	}
	sort(V.begin(), V.end());
	vector<pair<int,pair<int,int>>> left;
	for (int i=0; i<V.size(); ++i){
		int v = V[i].second.first, u = V[i].second.second, d = V[i].first;
		if (!merge(v, u, d))
			left.push_back(V[i]);
		else{
			graph[v].push_back(make_pair(u, d));
			graph[u].push_back(make_pair(v, d));
			mst += d;
		}
	}
	for (int i=1; i<=N; ++i){
		if (graph[i].size() == 0){
			cout << -1;
			return 0;
		}
	}
	if (M <= N - 1){
		cout << -1;
		return 0;
	}
	dfs(1, -1, -1);
	for (int i=1; i<=16; ++i){
		for (int j=1; j<=N; ++j){
			if (par[i-1][j] != -1){
				par[i][j] = par[i-1][par[i-1][j]];
				maxedge[i][j] = max(maxedge[i-1][j], maxedge[i-1][par[i-1][j]]);
				// cout << i << " " << j << " " << par[i][j] << " " << maxedge[i][j] << endl;
			}
		}
	}
	int best = 1e9;
	for (int i=0; i<left.size(); ++i){
		int v = left[i].second.first, u = left[i].second.second, d = left[i].first;
		int md = findmax(v, u);
		// cout << md << endl;
		if (d != md)
			best = min(best, mst + d - md);
	}
	if (best == 1e9)
		cout << -1;
	else
		cout << best << endl;



	return 0;
}