#include <bits/stdc++.h>
//Qsqrt(N) - sqrt decomposition
using namespace std;

int qs[300010][3];
int n, nq;

struct DSU{
	int root[30010];
	void setup(){
		for (int i=1; i<=n; ++i) root[i] = i;
	}
	int find(int v){
		if (root[v] == v) return v;
		return root[v] = find(root[v]);
	}
	void merge(int v, int u){
		v = find(v); u = find(u);
		if (v == u) return;
		root[v] = u;
	}
} dsu, dsu2;

int val[30010], depth[30010], to[30010], from[30010], bestmod = 0, par[16][30010], gmod;
vector<int> g[30010];
vector<int> grps[1010];
int jumpsum[30010], jumppar[30010];
int vcnt = 0;

bool past[30010];
void dfs(int v, int p){
	depth[v] = depth[p] + 1;
	par[0][v] =  p;
	for (int i=1; i<=15; ++i){
		par[i][v] = par[i-1][par[i-1][v]];
	}
	to[v] = ++vcnt;
	// cout << depth[v] << " " << gmod << endl;
	grps[depth[v]%gmod].push_back(v);
	for (int u : g[v]){
		if (u == p) continue;
		dfs(u, v);
	}
	from[v] = vcnt;
}

int lca(int v, int u){
	if (depth[u] > depth[v]) swap(v, u);
	int diff = depth[v] - depth[u];
	for (int i=15; i>=0; --i){
		if ((1 << i) <= diff){
			diff -= (1 << i);
			v = par[i][v];
		}
	}
	if (v == u) return v;
	for (int i=15; i>=0; --i){
		if (par[i][v] != par[i][u]){
			u = par[i][u];
			v = par[i][v];
		}
	}
	return par[0][v];
}

int main(){
	// freopen("test.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> val[i];
	}
	dsu.setup();
	dsu2.setup();
	cin >> nq;
	for (int i=0; i<nq; ++i){
		string S; cin >> S;
		if (S == "excursion") qs[i][0] = 0;
		else if (S == "bridge") qs[i][0] = 1;
		else if (S == "penguins") qs[i][0] = 2;
		cin >> qs[i][1] >> qs[i][2];

		if (qs[i][0] == 1 && dsu2.find(qs[i][1]) != dsu2.find(qs[i][2])){
			dsu2.merge(qs[i][1], qs[i][2]);
			g[qs[i][1]].push_back(qs[i][2]);
			g[qs[i][2]].push_back(qs[i][1]);
		}
	}
	gmod = 180;
	// gmod = 1000;

	for (int i=1; i<=n; ++i){
		if (to[i] == 0) dfs(i, i);
	}
	bestmod = 1;
	for (int i=1; i<gmod; ++i){
		if (grps[i].size() < grps[bestmod].size()) bestmod = i;
	}
	// cout << grps[0].size() << endl;
	for (int x : grps[bestmod]){
		if (depth[x] <= gmod) continue;
		int y = x;
		int cnt = 0;
		while (depth[x] - depth[y] != gmod){
			jumpsum[x] += val[y];
			y = par[0][y];
		}
		jumppar[x] = y;
	}
	for (int i=0; i<nq; ++i){
		int v = qs[i][1], u = qs[i][2];
		if (qs[i][0] == 0){ //this is query
			if (dsu.find(v) != dsu.find(u)){
				cout << "impossible\n";
				continue;
			}
			//found it;
			int p = lca(v, u);
			//let's do the stupid way
			int ans = 0;
			if (depth[v] - depth[p] > 2*gmod){
				while (depth[v]%gmod != bestmod){
					ans += val[v];
					v = par[0][v];
				}
				while (depth[v] - depth[p] > gmod){
					ans += jumpsum[v];
					v = jumppar[v];
				}
			}

			if (depth[u] - depth[p] > 2*gmod){
				while (depth[u]%gmod != bestmod){
					ans += val[u];
					u = par[0][u];
				}
				while (depth[u] - depth[p] > gmod){
					ans += jumpsum[u];
					u = jumppar[u];
				}
			}

			while (v != p){
				ans += val[v];
				v = par[0][v];
			}

			while (u != p){
				ans += val[u];
				u = par[0][u];
			}
			ans += val[p];
			cout << ans << '\n';
		}
		else if (qs[i][0] == 1){
			if (dsu.find(v) == dsu.find(u)) cout << "no\n";
			else cout << "yes\n";
			dsu.merge(v, u);
		}
		else if (qs[i][0] == 2){
			for (int x : grps[bestmod]){
				if (to[v] <= to[x] && to[x] <= from[v] && depth[x] - depth[v] < gmod){
					jumpsum[x] += u - val[v];
				}
			}
			val[v] = u;
		}
	}

	return 0;
}