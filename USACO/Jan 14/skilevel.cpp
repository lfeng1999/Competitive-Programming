#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct Edge{
	int v, u, d;
	bool operator < (const Edge &a) const {return d < a.d;}
};

int R, C, grid[510][510], T;
int rnk[260010], root[260010], ans[260010], sz[260010];

void merge(int v, int u){
	if (rnk[v] < rnk[u]) swap(v, u);
	root[u] = v;
	if (rnk[v] == rnk[u]) rnk[v]++;
	sz[v] += sz[u];
}
int find(int v){
	int rt = root[v];
	if (rt != root[rt]) find(rt); //do the compression
	if (ans[v] == -1){
		if (ans[rt] == -1) ans[v] = ans[root[rt]];
		else ans[v] = ans[rt];
		// ans[v] = min(ans[rt], ans[root[rt]]); You can't do this. 
		// the root[rt] might have a smaller answer than that of ans[rt] so u can't.
	}
	root[v] = root[rt]; //compress
	return root[v];
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("skilevel.in","r",stdin);
	freopen("skilevel.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> R >> C >> T;
	for (int i=0; i<R; ++i){for (int j=0; j<C; ++j) cin >> grid[i][j];}
	vector<Edge> edges;
	for (int i=0; i<R; ++i){
		for (int j=0; j<C; ++j){
			if (i != 0){
				edges.push_back({i*C+j, (i-1)*C+j, abs(grid[i][j] - grid[i-1][j])});
			}
			if (j != 0){
				edges.push_back({i*C+j, i*C+(j-1), abs(grid[i][j] - grid[i][j-1])});
			}
		}
	}
	for (int i=0; i<R*C; ++i){
		root[i] = i; sz[i] = 1; rnk[i] = 0; ans[i] = -1;
	}
	sort(edges.begin(), edges.end());
	for (auto &it : edges){
		int v = it.v, u = it.u, d = it.d;
		v = find(v), u = find(u);
		if (v == u) continue;
		if (sz[v] + sz[u] >= T){
			if (sz[v] < T){
				ans[v] = d;
			}
			if (sz[u] < T){
				ans[u] = d;
			}
		}
		merge(v, u);
	}
	lint finans = 0;
	for (int i=0; i<R; ++i){
		for (int j=0; j<C; ++j){
			int x; cin >> x;
			if (x == 0) continue;
			find(i*C+j);
			finans += ans[i*C+j];
		}
	}
	cout << finans;

	return 0;
}