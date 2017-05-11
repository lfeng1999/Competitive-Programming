#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
vector<pair<int,lint>> graph[200010];
lint rad;
int to[200010], from[200010], vcnt = 0, n, ans[200010];

struct SegmentTree{
	lint seg[600010], lazy[600010];
	int cnt[600010];
	void reset(){memset(seg, 0, sizeof(seg));}
	void turnon(int v, int L, int R, int p){
		if (L == R){seg[v] = 0; cnt[v] = 1; return;}
		if (p <= (L+R)/2) turnon(v*2, L, (L+R)/2, p);
		else turnon(v*2+1, (L+R)/2+1, R, p);
		cnt[v] = cnt[v*2] + cnt[v*2+1];
	}
	void push_lazy(int v, int L, int R){
		seg[v] += lazy[v];
		if (v*2 < 600010){
			lazy[v*2] += lazy[v]; lazy[v*2+1] += lazy[v];
		}
		lazy[v] = 0;
		if (seg[v] > rad){
			if (L == R){
				cnt[v] = 0;
				seg[v] = -1e9;
				return;
			}
			push_lazy(v*2, L, (L+R)/2);
			push_lazy(v*2+1, (L+R)/2+1, R);
			seg[v] = max(seg[v*2], seg[v*2+1]);
			cnt[v] = cnt[v*2] + cnt[v*2+1];
			return;
		}
	}
	void update(int v, int L, int R, int UL, int UR, lint val){
		push_lazy(v, L, R);
		if (UL <= L && R <= UR){
			lazy[v] = val; push_lazy(v, L, R);
			return;
		}
		if (UR < L || R < UL) return;
		update(v*2, L, (L+R)/2, UL, UR, val);
		update(v*2+1, (L+R)/2+1, R, UL, UR, val);
		seg[v] = max(seg[v*2], seg[v*2+1]);
		cnt[v] = cnt[v*2] + cnt[v*2+1];
	}
	int query(int v, int L, int R, int QL, int QR){
		if (QL <= L && R <= QR) return cnt[v];
		if (R < QL || QR < L) return 0;
		return query(v*2, L, (L+R)/2, QL, QR) + query(v*2+1, (L+R)/2+1, R, QL, QR);
	}
};
SegmentTree seg;


void dfs(int v){
	to[v] = ++vcnt;
	for (auto &it : graph[v]){
		int u = it.first;
		dfs(u);
	}
	from[v] = vcnt;
}

void solve(int v){
	seg.turnon(1, 1, n, to[v]);
	for (auto &E : graph[v]){
		int u = E.first; lint d = E.second;
		solve(u);
		seg.update(1, 1, n, to[u], from[u], d);
	}
	ans[v] = seg.query(1, 1, n, to[v], from[v]);
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("runaway.in","r",stdin);
	freopen("runaway.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> rad;
	for (int i=2; i<=n; ++i){
		int p; lint d; cin >> p >> d;
		graph[p].push_back(make_pair(i, d));
	}
	dfs(1);
	solve(1);
	for (int i=1; i<=n; ++i){
		cout << ans[i] << '\n';
	}
	return 0;
}