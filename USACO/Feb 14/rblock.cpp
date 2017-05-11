#include <bits/stdc++.h>

using namespace std;

int graph[251][251], n, m;
int sd[251], pre[251];
bool past[251];

int solve(bool need = false){
	fill(sd, sd+251, 1e9);
	memset(past, false, sizeof(past));
	sd[1] = 0;
	for (int qq=0; qq<n; ++qq){
		int v = -1, d = 1e9;
		for (int i=1; i<=n; ++i){
			if (!past[i] && sd[i] < d){
				d = sd[i];
				v = i;
			}
		}
		past[v] = true;
		for (int u=1; u<=n; ++u){
			if (sd[u] > sd[v] + graph[v][u]){
				sd[u] = sd[v] + graph[v][u];
				if (need) pre[u] = v;
			}
		}
	}
	return sd[n];
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("rblock.in","r",stdin);
	freopen("rblock.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; ++i) fill(graph[i], graph[i] + 251, 1e9);
	for (int qq=0; qq<m; ++qq){
		int v, u, d; cin >> v >> u >> d;
		graph[v][u] = graph[u][v] = d;
	}
	int furthest = solve(true);
	int ed = n, best = 0;
	while (ed != 1){
		graph[ed][pre[ed]] *= 2;
		graph[pre[ed]][ed] *= 2;
		best = max(best, solve());
		graph[ed][pre[ed]] /= 2;
		graph[pre[ed]][ed] /= 2;
		ed = pre[ed];
	}
	cout << best - furthest;
	return 0;
}