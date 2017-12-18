#include <bits/stdc++.h>

using namespace std;

vector<int> g[100010];
int to[100010], from[100010], depth[100010], par[17][100010], low_link[100010], vcnt = 0;

void dfs(int v, int p){
	to[v] = low_link[v] = ++vcnt;
	par[0][v] = p;
	depth[v] = depth[p] + 1;
	for (int i=1; i<17; ++i){
		par[i][v] = par[i-1][par[i-1][v]];
	}
	for (int u : g[v]){
		if (u == p) continue;
		if (to[u] != 0){
			low_link[v] = min(low_link[v], to[u]);
		}
		else{
			dfs(u, v);
			low_link[v] = min(low_link[v], low_link[u]);
		}
	}
	from[v] = vcnt;
}

int is_child(int v, int p){
	return to[p] <= to[v] && to[v] <= from[p];
}

int direct_child(int v, int p){
	int diff = depth[v] - depth[p];
	for (int i=16; i>=0; --i){
		if (diff - (1 << i) > 0){
			diff -= (1 << i);
			v = par[i][v];
		}
	}
	return v;
}

int n, m, es[500010][2];

int main(){
	// freopen("test.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;

	for (int i=1; i<=m; ++i){
		int v, u;
		cin >> v >> u;
		g[v].push_back(u);
		g[u].push_back(v);
		es[i][0] = v, es[i][1] = u;
	}
	dfs(1, 0);
	int nq; cin >> nq;
	for (int qq=0; qq<nq; ++qq){
		int typ; cin >> typ;
		// cout << qq + 1 << ". ";
		if (typ == 1){
			int a, b, p1, p2;
			cin >> a >> b >> p1 >> p2;
			if (to[p1] < to[p2]) swap(p1, p2);
			bool ch1 = is_child(a, p1), ch2 = is_child(b, p1);
			if (par[0][p1] != p2){
				cout << "yes\n";
			}
			else if (low_link[p1] <= to[p2]){
				cout << "yes\n";
			}
			else if (ch1 && ch2){
				cout << "yes\n";
			}
			else if (!ch1 && !ch2){
				cout << "yes\n";
			}
			else{
				cout << "no\n";
			}
		}
		else if (typ == 2){
			int a, b, c; cin >> a >> b >> c;
			bool ch1 = is_child(a, c), ch2 = is_child(b, c);
			if (ch2){
				swap(a, b);
				swap(ch1, ch2);
			}

			if (ch1 && ch2){
				int dc1 = direct_child(a, c), dc2 = direct_child(b, c);
				if (dc1 == dc2) cout << "yes\n";
				else if (low_link[dc1] < to[c] && low_link[dc2] < to[c]) cout << "yes\n";
				else cout << "no\n";
			}
			else if (ch1 && !ch2){
				int dchild = direct_child(a, c);
				if (low_link[dchild] < to[c]) cout << "yes\n";
				else cout << "no\n";
			}
			else if (!ch1 && !ch2){
				cout << "yes\n";
			}
		}
		// cout << endl;
	}
	return 0;
}