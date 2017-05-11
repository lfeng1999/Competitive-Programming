#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	int seg[540010];
	void reset(){fill(seg, seg+540010, -1e9);}
	void update(int v, int L, int R, int p, int val){
		if (L == R){seg[v] = max(seg[v], val); return;}
		if (p <= (L+R)/2) update(v*2, L, (L+R)/2, p, val);
		else update(v*2+1, (L+R)/2+1, R, p, val);
		seg[v] = max(seg[v*2], seg[v*2+1]);
	}
	int query(int v, int L, int R, int QL, int QR){
		if (R < QL || QR < L) return -1e9;
		if (QL <= L && R <= QR) return seg[v];
		return max(query(v*2, L, (L+R)/2, QL, QR), query(v*2+1, (L+R)/2+1, R, QL, QR));
	}
} seg;

int maxx[200010], minxx[200010], n, m;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(minxx, minxx+200010, 1e9);
	cin >> n >> m;
	for (int qq=0; qq<m; ++qq){
		int l, r; cin >> l >> r;
		minxx[r] = min(minxx[r], l);
		maxx[r] = max(maxx[r], l);
	}
	for (int i=n; i>=0; --i){
		minxx[i] = min(minxx[i], minxx[i+1]);
	}
	for (int i=1; i<=n+1; ++i){
		maxx[i] = max(maxx[i], maxx[i-1]);
	}
	seg.reset();
	seg.update(1, 0, n+1, 0, 0);
	for (int i=1; i<=n+1; ++i){
		int l = maxx[i-1], r = minxx[i] - 1;
		if (l > r) continue;
		// cout << i << " " << seg.query(1, 0, n+1, l, r) + 1 << endl;
		seg.update(1, 0, n+1, i, seg.query(1, 0, n+1, l, r) + 1);
	}
	int ans = seg.query(1, 0, n+1, n+1, n+1) - 1;
	if (ans < 0) ans = -1;
	cout << ans;
	return 0;
}