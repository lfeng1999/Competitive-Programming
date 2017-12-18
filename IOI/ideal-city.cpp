#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const lint MOD = 1e9;
lint n, sx, sy, v_cnt;
vector<lint> xs[200010], ys[200010];
set<lint> grid[2][200010];
map<lint,lint> comp[200010];
set<lint> graph[200100];
lint subsz[200100];

lint dfs(lint v, lint p, lint tot){
	lint ret = 0;
	for (lint u : graph[v]){
		if (u == p) continue;
		ret += dfs(u, v, tot);
		subsz[v] += subsz[u];
	}
	ret += subsz[v] * (tot - subsz[v]);
	ret %= MOD;
	// cout << subsz[v] << " " << tot - subsz[v] << " " << ret << endl;
	return ret;
}

lint solve(lint id){
	memset(subsz, 0, sizeof(subsz));
	for (lint i=1; i<200010; ++i){
		graph[i].clear();
		comp[i].clear();
	}

	v_cnt = 0;
	lint n_cnt = 0;
	for (lint x=1; x<200010; ++x){
		lint cur = -100;
		for (lint y : grid[id][x]){
			if (y != cur + 1){
				n_cnt++;
			}
			cur = y;
			comp[x][y] = n_cnt;
			subsz[n_cnt]++;
			// cout << x - 100000 << " " << y - 100000 << " " << n_cnt << endl;
			if (grid[id][x-1].count(y)){
				graph[n_cnt].insert(comp[x-1][y]);
				graph[comp[x-1][y]].insert(n_cnt);
				// cout << n_cnt << " " << comp[x-1][y] << endl;
			}
		}
	}
	return dfs(1, -1, n);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	cin >> sx >> sy;
	grid[0][100000].insert(100000);
	grid[1][100000].insert(100000);
	for (lint qq=1; qq<n; ++qq){
		lint x, y; cin >> x >> y;
		x -= sx; x += 100000;
		y -= sy; y += 100000;
		grid[0][x].insert(y);
		grid[1][y].insert(x);
	}
	cout << (solve(0) + solve(1))%MOD;

	return 0;
}