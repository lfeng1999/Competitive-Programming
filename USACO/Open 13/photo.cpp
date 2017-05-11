#include <bits/stdc++.h>

using namespace std;

struct SEGMENTTREE{
	int seg[600010];
	void build_tree(int v, int L, int R){
		seg[v] = -1e9;
		if (L == R) return;
		build_tree(v*2, L, (L+R)/2); build_tree(v*2+1, (L+R)/2+1, R);
	}
	void update(int v, int L, int R, int p, int val){
		if (L == R){seg[v] = val; return;}
		if (p <= (L+R)/2) update(v*2, L, (L+R)/2, p, val);
		else update(v*2+1, (L+R)/2+1, R, p, val);
		seg[v] = max(seg[v*2], seg[v*2+1]);
	}
	int query(int v, int L, int R, int QL, int QR){
		if (QR < L || R < QL) return -1e9;
		if (QL <= L && R <= QR) return seg[v];
		return max(query(v*2, L, (L+R)/2, QL, QR), query(v*2+1, (L+R)/2+1, R, QL, QR));
	}
} seg;

int minb[200010], maxb[200010], n, m;

int main(){
	freopen("test.txt","r",stdin);
	// freopen("photo.in","r",stdin);
	// freopen("photo.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(minb, minb+200010, 1e9);
	cin >> n >> m;
	for (int i=0; i<=n; ++i) maxb[i] = i;
	for (int qq=0; qq<m; ++qq){
		int l, r; cin >> l >> r;
		maxb[l] = max(maxb[l], r); //maxbegin
		minb[l] = min(minb[l], r); //minbegin
	}
	minb[n+1] = n+1;
	for (int i=n; i>=1; --i){
		minb[i] = min(minb[i], minb[i+1]);
	}
	for (int i=1; i<=n; ++i){
		maxb[i] = max(maxb[i], maxb[i-1]);
	}
	seg.build_tree(1, 0, n+1);
	seg.update(1, 0, n+1, n+1, 0);
	for (int i=n; i>=0; --i){
		int l = maxb[i]+1, r = minb[i+1];
		if (l > r) continue;
		int val = seg.query(1, 0, n+1, l, r);
		seg.update(1, 0, n+1, i, val+1);
	}
	int ans = seg.query(1, 0, n+1, 0, 0) - 1;
	if (ans < 0) ans = -1;
	cout << ans;

	return 0;
}