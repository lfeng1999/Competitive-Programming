#include <bits/stdc++.h>

using namespace std;

int N, K[200010], plen[200010], npath[200010];
vector<int> graph[200010];

void dfs(int v, int p){
	npath[v] = 1;
	plen[v] = 0;
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
		npath[v] += npath[u];
		plen[v] += plen[u] + npath[u];
	}
}
int ptot[200010];
void dfs2(int v, int p){
	if (p != -1){
		ptot[v] += (plen[v])*(npath[p] - npath[v]);
		ptot[v] += plen[v];
		ptot[v] += (plen[p] - plen[v] - npath[v])*npath[v];
		ptot[v] += npath[v] * (npath[p] - npath[v]);

		plen[v] += plen[p] - plen[v] - npath[v] + npath[p] - npath[v];
		npath[v] += npath[p] - npath[v];
	}
	else{
		for (int u : graph[v]){
			ptot[v] += (plen[u] + npath[u])*(npath[v] - npath[u]);
		}
	}
	for (int u : graph[v]){
		if (u == p) continue;
		dfs2(u, v);
	}
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=1; i<=N; ++i){
		cin >> K[i];
	}
	for (int i=0; i<N-1; ++i){
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	dfs(1, -1);
	dfs2(1, -1);
	int ans = 0;
	for (int i=1; i<=N; ++i){
		ans += ptot[i]*K[i];
		// cout << i << " " << ptot[i] << endl;
	}
	cout << ans;
	return 0;
}