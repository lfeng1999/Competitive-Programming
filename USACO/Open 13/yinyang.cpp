#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

int n;
vector<pair<int,int>> graph[100010];
int subsz[100010], par[100010];
bool cent[100010];
void dfs(int v, int p){
	subsz[v] = 1;
	par[v] = 0;
	for (auto &e : graph[v]){
		int u = e.first;
		if (cent[u] || u == p) continue;
		dfs(u, v); subsz[v] += subsz[u];
		if (par[v] == 0 || subsz[u] > subsz[par[v]]){
			par[v] = u;
		}
	}
}
int to[100010], from[100010], vcnt = 0;
void dfs2(int v, int p){
	to[v] = ++vcnt;
	for (auto &e : graph[v]){
		if (e.first == p || cent[e.first]) continue;
		dfs2(e.first, v);
	}
	from[v] = vcnt;
}
lint ans = 0;
map<int, vector<int>> cnt1;
map<int,lint> only1, more, temponly1, tempmore;
void setup(int v, int p, int val){
	cnt1[val].push_back(v);
	for (auto &e : graph[v]){
		if (e.first == p || cent[e.first]) continue;
		setup(e.first, v, val + e.second);
	}
}

void solve(int v){
	dfs(v, v);
	int tot = subsz[v];
	while (subsz[par[v]]*2 >= tot) v = par[v];
	vcnt = 0;
	dfs2(v, v);  
	cent[v] = true;
	only1.clear(); more.clear();
	for (auto &e : graph[v]){
		if (cent[e.first]) continue;
		cnt1.clear(); tempmore.clear(); temponly1.clear();
		setup(e.first, v, e.second);
		for (auto &vec : cnt1){
			int maxfrom = 0;
			int add1 = 0, addmore = 0;
			for (auto u : vec.second){
				if (to[u] > maxfrom){
					maxfrom = from[u];
					add1++;
				}
				else{
					addmore++;
				}
			}
			if (vec.first == 0){
				ans += addmore; //at the root
				ans += add1*more[0];
				ans += addmore*(only1[0] + more[0]);
				tempmore[vec.first] += add1 + addmore;
			}
			else{
				ans += add1*more[-vec.first];
				ans += addmore*(only1[-vec.first] + more[-vec.first]);
				temponly1[vec.first] += add1;
				tempmore[vec.first] += addmore;
			}
		}
		for (auto &it : temponly1){
			only1[it.first] += it.second;
		}
		for (auto &it : tempmore){
			more[it.first] += it.second;
		}
	}
	for (auto &e : graph[v]) if (!cent[e.first]) solve(e.first);
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("yinyang.in","r",stdin);
	freopen("yinyang.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n-1; ++i){
		int v, u, t; cin >> v >> u >> t;
		if (t == 0) t = -1;
		graph[v].push_back(make_pair(u, t)); graph[u].push_back(make_pair(v, t));
	}
	solve(1);
	cout << ans;
	return 0;
}