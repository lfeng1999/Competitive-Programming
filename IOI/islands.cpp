#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
struct Edge{
	int v, u, d;
} es[2000010];

int n, dtime = 0, disc[1000010], low_link[1000010];
vector<int> g[1000010];
bool in_cycle[1000010];
int par[1000010], pdist[1000010];
lint val[1000010];
stack<int> stk;
vector<int> cyc;

void tarjan(int v, int pedge){
	stk.push(v);
	disc[v] = low_link[v] = ++dtime;
	for (lint nedge : g[v]){
		if (nedge == (pedge^1)) continue;
		int u = es[nedge].u, d = es[nedge].d;
		// cout << v << " " << u << endl;
		if (disc[u]){
			low_link[v] = min(low_link[v], disc[u]);
		}
		else{
			tarjan(u, nedge);
			low_link[v] = min(low_link[v], low_link[u]);
			par[u] = v; pdist[u] = d;
		}
	}
	if (disc[v] == low_link[v]){
		if (stk.top() == v) stk.pop();
		else{
			while (stk.top() != v){
				in_cycle[stk.top()] = true;
				cyc.push_back(stk.top());
				stk.pop();
			}
			in_cycle[stk.top()] = true;
			cyc.push_back(stk.top()); stk.pop();
		}
	}
}

void setup_dfs(int v, int p){
	for (int x : g[v]){
		int u = es[x].u, d = es[x].d;
		if (in_cycle[u] || u == p) continue;
		setup_dfs(u, v);
		val[v] = max(val[v], val[u] + d);
	}
}
int invalid_edge;

pair<lint,int> furthest(int v, int p){
	pair<lint,int> ret = {0, v};
	for (int x : g[v]){
		int u = es[x].u, d = es[x].d;
		if (x == invalid_edge || (x^1) == invalid_edge || u == p) continue;
		pair<lint,int> cur = furthest(u, v);
		cur.first += d;
		if (cur > ret) ret = cur;
	}
	return ret;
}

lint get_diameter(lint v){
	v = furthest(v, -1).second;
	return furthest(v, -1).first;
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int v = 1; v <= n; ++v){
		int u, d; cin >> u >> d;
		es[v*2 - 2] = {v, u, d};
		es[v*2 - 1] = {u, v, d};
		g[v].push_back(v*2 - 2);
		g[u].push_back(v*2 - 1);
	}
	lint ans = 0;
	for (lint v=1; v<=n; ++v){
		if (disc[v] != 0 || g[v].size() == 1) continue;
		tarjan(v, -1);

		if (cyc.size() == 2){//just bash small case
			lint tmpans = 0;
			for (int y : cyc){
				for (int x : g[y]){
					if (in_cycle[es[x].u]){
						invalid_edge=x;
						tmpans = max(tmpans, get_diameter(cyc[0]));
					}
				}
			}
			ans += tmpans;
			cyc.clear();
			continue;
		}


		for (int x : cyc) setup_dfs(x, -1);




		for (int x : g[cyc[0]]){
			if (in_cycle[es[x].u]){
				invalid_edge = x;
				break;
			}
		}
		lint tmpans = get_diameter(cyc[0]);



		lint totdist = 0;
		deque<pair<lint,int>> Q; // stores max val - dist
		for (int i=0; i<cyc.size()*2 - 1; ++i){
			int u = cyc[i%cyc.size()], w = cyc[(i+1)%cyc.size()], d;
			for (int x : g[u]){
				int nu = es[x].u, nd = es[x].d;
				if (w == nu){
					d = nd;
					break;
				}
			}
			if (Q.front().second == u) Q.pop_front();
			if (i != 0){
				tmpans = max(tmpans, Q.front().first + totdist + val[u]);
			}
			pair<lint,int> toadd = {val[u] - totdist, u};
			while (!Q.empty() && Q.back() < toadd){
				Q.pop_back();
			}
			Q.push_back(toadd);
			totdist += d;
		}




		ans += tmpans;
		cyc.clear();
	}
	cout << ans;
	return 0;
}