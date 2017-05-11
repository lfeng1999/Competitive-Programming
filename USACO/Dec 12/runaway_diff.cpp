#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

int par[18][200010], n, a[200010];
lint dep[200010], rad;
vector<pair<int,lint>> graph[200010];

void dfs(int v, int p, lint d){
	par[0][v] = p; dep[v] = d;
	for (int i=1; i<18; ++i) if (par[i-1][v] != -1) par[i][v] = par[i-1][par[i-1][v]];
	for (auto e : graph[v]){
		dfs(e.first, v, d + e.second);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("runaway.in","r",stdin);
	freopen("runaway.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<18; ++i) fill(par[i], par[i]+200010, -1);
	cin >> n >> rad;
	for (int i=2; i<=n; ++i){
		int p; lint len; cin >> p >> len;
		graph[p].push_back({i, len});
	}
	dfs(1, -1, 0);
	for (int v=1; v<=n; ++v){
		lint tmp = rad, cv = v;
		for (int i=17; i>=0; --i){
			if (par[i][cv] != -1 && dep[cv] - dep[par[i][cv]] <= tmp){
				tmp -= dep[cv] - dep[par[i][cv]];
				cv = par[i][cv];
			}
		}
		a[v]++;
		if (cv != -1) a[par[0][cv]]--;
	}
	for (int v=n; v>=2; --v){
		a[par[0][v]] += a[v];
	}
	for (int v=1; v<=n; ++v){
		cout << a[v] << '\n';
	}
	return 0;
}