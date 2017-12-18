#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
struct Edge{
	lint v, u, d;
} es[2000010];

lint n, dtime = 0, disc[1000010], low_link[1000010];
vector<lint> g[1000010];
bool in_cycle[1000010];
lint par[1000010], pdist[1000010], val[1000010];
stack<lint> stk;
vector<lint> cyc, nodes;

void tarjan(lint v, lint pedge){
	stk.push(v); nodes.push_back(v);
	disc[v] = low_link[v] = ++dtime;
	for (lint nedge : g[v]){
		if (nedge == (pedge^1)) continue;
		lint u = es[nedge].u, d = es[nedge].d;
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

void setup_dfs(lint v, lint p){
	for (lint x : g[v]){
		lint u = es[x].u, d = es[x].d;
		if (in_cycle[u] || u == p) continue;
		setup_dfs(u, v);
		val[v] = max(val[v], val[u] + d);
	}
}
lint invalid_edge;

pair<lint,lint> furthest(lint v, lint p){
	pair<lint,lint> ret = {0, v};
	for (lint x : g[v]){
		lint u = es[x].u, d = es[x].d;
		if (x == invalid_edge || (x^1) == invalid_edge || u == p) continue;
		pair<lint,lint> cur = furthest(u, v);
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
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (lint v = 1; v <= n; ++v){
		lint u, d; cin >> u >> d;
		es[v*2 - 2] = {v, u, d};
		es[v*2 - 1] = {u, v, d};
		g[v].push_back(v*2 - 2);
		g[u].push_back(v*2 - 1);
	}
	lint ans = 0;
	for (lint v=1; v<=n; ++v){
		if (disc[v] != 0 || g[v].size() == 1) continue;
		tarjan(v, -1);

		for (lint x : cyc) setup_dfs(x, -1);

		lint lol = 0;
		for (int y : cyc){
			for (lint x : g[y]){
				if (in_cycle[es[x].u]){
					invalid_edge = x;
					lol = max(lol, get_diameter(cyc[0]));
					// break; 
				}
			}
		}
		// lint tmpans = get_diameter(cyc[0]);
		ans += lol;
		cyc.clear();
		nodes.clear();
	}
	cout << ans;
	return 0;
}