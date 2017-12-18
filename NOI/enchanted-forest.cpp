#include <bits/stdc++.h>

using namespace std;

int n, m;
struct DSU{
	int root[50010], rnk[50010];
	void reset(){
		for (int i=1; i<=n; ++i){
			root[i] = i;
			rnk[i] = 0;
		}
	}
	int find(int v){
		if (v == root[v]) return v;
		return root[v] = find(root[v]);
	}
	void merge(int v, int u){
		v = find(v); u = find(u);
		if (v == u) return;
		if (rnk[v] > rnk[u]) swap(v, u);
		if (rnk[v] == rnk[u]) rnk[u]++;
		root[v] = u;
	}
} dsu;
struct Edge{
	int v, u, a, b;
};
vector<Edge> es;
bool sorta(Edge a, Edge b){
	return a.a < b.a;
}

int getidx(int limB){
	dsu.reset();
	for (int i=0; i<m; ++i){
		if (es[i].b > limB) continue;
		dsu.merge(es[i].v, es[i].u);
		if (dsu.find(1) == dsu.find(n)){
			return es[i].a;
		}
	}
	return -1;
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;

	set<int> bs;
	for (int qq=0; qq<m; ++qq){
		int v, u, a, b; cin >> v >> u >> a >> b;
		es.push_back({v, u, a, b});
		bs.insert(b);
	}
	sort(es.begin(), es.end(), sorta);
	int ans = 2e9;
	for (int limB = 1; limB <= 50000; ++limB){
		int curidx = getidx(limB);
		if (curidx != -1)
			ans = min(ans, curidx + limB);
		for (int i=16; i>=0; --i){
			if (curidx + (1 << i) <= 50000 && curidx == getidx(limB + (1 << i))){
				limB += (1 << i);
			}
		}
	}
	if (ans == 2e9)
		ans = -1;
	cout << ans;

	return 0;
}