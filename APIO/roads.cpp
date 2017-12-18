#include <bits/stdc++.h>

using namespace std;

int n, m, req;

struct DSU{
	int root[20010];

	void reset(){
		for (int i=1; i<=n; ++i)
			root[i] = i;
	}
	int find(int v){
		if (v == root[v]) return v;
		return root[v] = find(root[v]);
	}
	void merge(int v, int u){
		v = find(v); u = find(u);
		if (v == u) return;
		root[v] = u;
	}
}dsu;

vector<pair<int,int>> es[2];
set<pair<int,int>> used;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> req;
	for (int i=0; i<m; ++i){
		int v, u, typ; cin >> v >> u >> typ;
		es[typ].push_back({v, u});
	}
	dsu.reset();
	vector<pair<int,int>> ans;
	for (auto it : es[1]){
		dsu.merge(it.first, it.second);
	}
	int cnt = 0;
	for (auto it : es[0]){
		if (dsu.find(it.first) == dsu.find(it.second)) continue;
		dsu.merge(it.first, it.second);
		used.insert(it);
		ans.push_back(it);
		++cnt;
	}
	bool valid = true;
	int rt = dsu.find(1);
	for (int i=1; i<=n; ++i){
		if (dsu.find(i) != rt)
			valid = false;
	}
	if (ans.size() > req || !valid){
		cout << "no solution";
		return 0;
	}
	dsu.reset();
	for (auto it : ans){
		dsu.merge(it.first, it.second);
	}
	for (auto it : es[0]){
		if (used.count(it) != 0 || dsu.find(it.first) == dsu.find(it.second)) continue;
		dsu.merge(it.first, it.second);
		ans.push_back(it);
		if (ans.size() == req) break;
	}
	if (ans.size() != req){
		cout << "no solution";
		return 0;
	}
	for (auto it : ans){
		cout << it.first << " " << it.second << " " << 0 << '\n';
	}

	for (auto it : es[1]){
		if (dsu.find(it.first) == dsu.find(it.second)) continue;
		dsu.merge(it.first, it.second);
		cout << it.first << " " << it.second << " " << 1 << '\n';
	}

	return 0;	
}