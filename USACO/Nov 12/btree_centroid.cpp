#include <bits/stdc++.h>

using namespace std;

vector<int> graph[40010];
char typ[40010];
int n;
bool cent[40010];
int subsz[40010], par[40010];

void dfs(int v, int p){
	subsz[v] = 1;
	par[v] = 0;	int best = 0;
	for (int u : graph[v]){
		if (u == p || cent[u]) continue;
		dfs(u, v); subsz[v] += subsz[u];
		if (par[v] == 0 || subsz[u] > subsz[par[v]]){
			par[v] = u; //path that leads to centroid
			best = subsz[u];
		}
	}
}
map<int,int> m1, m2;
vector<pair<int,int>> ta, tb;

void solve1(int v, int p, int sum, int hi){
	sum += (typ[v] == ')'?1:-1);
	hi = max(hi, sum);
	ta.push_back(make_pair(sum, hi));
	
	for (int u : graph[v]){
		if (cent[u] || u == p) continue;
		solve1(u, v, sum, hi);
	}
}
void solve2(int v, int p, int sum, int hi){
	sum += (typ[v] == '('?1:-1);
	hi = max(hi, sum);
	tb.push_back(make_pair(sum, hi));
	
	for (int u : graph[v]){
		if (cent[u] || u == p) continue;
		solve2(u, v, sum, hi);
	}
}

int ans = 0;

int wtf = 0;
void solve(int v){
	dfs(v, v);
	int tot = subsz[v];
	while (subsz[par[v]]*2 >= tot){
		v = par[v];
	}
	cent[v] = true; //found centroid
	for (int i=0; i<graph[v].size(); ++i){
		int u = graph[v][i];
		if (cent[u]) continue;
		solve1(u, v, (typ[v] == ')'?1:-1), (typ[v] == ')'?1:0));
		solve2(u, v, 0, 0);

		for (auto &it : ta){
			if (m2.count(it.first)){
				ans = max(ans, max(m2[it.first], it.second) - it.first);
			}
		}
		for (auto &it : tb){
			if (m1.count(it.first)){
				ans = max(ans, max(m1[it.first], it.second) - it.first);
			}
		}
		for (auto &it : ta){
			m1[it.first] = max(m1[it.first], it.second);
		}
		for (auto &it : tb){
			m2[it.first] = max(m2[it.first], it.second);
		}
		ta.clear(); tb.clear();
	}
	m1.clear(); m2.clear();
	for (int i=graph[v].size()-1; i>=0; --i){
		int u = graph[v][i];
		if (cent[u]) continue;
		solve1(u, v, (typ[v] == ')'?1:-1), (typ[v] == ')'?1:0));
		solve2(u, v, 0, 0);

		for (auto &it : ta){
			if (m2.count(it.first)){
				ans = max(ans, max(m2[it.first], it.second) - it.first);
			}
		}
		for (auto &it : tb){
			if (m1.count(it.first)){
				ans = max(ans, max(m1[it.first], it.second) - it.first);
			}
		}
		for (auto &it : ta){
			m1[it.first] = max(m1[it.first], it.second);
		}
		for (auto &it : tb){
			m2[it.first] = max(m2[it.first], it.second);
		}
		ta.clear(); tb.clear();
	}
	m1.clear(); m2.clear();

	for (int u : graph[v]){
		if (!cent[u])
			solve(u);
	}
}


int main(){
	// freopen("test.txt","r",stdin);
	freopen("btree.in","r",stdin);
	freopen("btree.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int v=2; v<=n; ++v){
		int p; cin >> p;
		graph[v].push_back(p); graph[p].push_back(v);
	}
	for (int i=1; i<=n; ++i){
		cin >> typ[i];
	}
	solve(1);
	cout << ans;
	return 0;
}