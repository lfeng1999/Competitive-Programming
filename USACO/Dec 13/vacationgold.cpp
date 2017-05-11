#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const lint INF = 1e18; //set to 1e9
typedef pair<lint, lint> pii;
struct Edge{
	lint v, u, d;
};

lint n, m, nhub, nq;
vector<pair<lint,lint>> graph[20010], rgraph[20010];
bool ishub[20010];
unordered_map<lint, vector<lint>> fromhub;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("vacationgold.in","r",stdin);
	freopen("vacationgold.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> n >> m >> nhub >> nq;
	vector<Edge> edges;
	for (lint i=0; i<m; ++i){
		lint v, u, d; cin >> v >> u >> d;
		graph[v].push_back(make_pair(u, d));
		// rgraph[u].push_back(make_pair(v, d));
	}
	for (lint qq=0; qq<nhub; ++qq){
		lint x; cin >> x; ishub[x] = true;
		fromhub[x] = vector<lint>(n+1, INF);
	}
	lint id = -1;
	for (lint i=1; i<=n; ++i){
		if (!ishub[i]) continue;
		priority_queue<pii, vector<pii>, greater<pii>> Q;
		Q.push(make_pair(0, i));
		fromhub[i][i] = 0;
		while (!Q.empty()){
			lint v = Q.top().second, d = Q.top().first;
			Q.pop();
			if (d > fromhub[i][v]) continue;
			for (auto &it : graph[v]){
				lint u = it.first, nd = d + it.second;
				if (nd < fromhub[i][u]){
					fromhub[i][u] = nd;
					Q.push(make_pair(nd, u));
				}
			}
		}
	}
	lint ans = 0, nans = 0;
	for (lint qq=0; qq<nq; ++qq){
		lint v, u; cin >> v >> u;
		lint tmp = INF;
		if (ishub[v]){
			tmp = fromhub[v][u];
		}
		else{
			for (auto &it : graph[v]){
				tmp = min(tmp, it.second + fromhub[it.first][u]);
			}
		}
		if (tmp < INF){
			ans += tmp;
			nans++;
		}
	}
	cout << nans << '\n' << ans;


	return 0;
}