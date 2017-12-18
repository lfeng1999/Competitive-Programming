#include <bits/stdc++.h>

using namespace std;

int lef[4000010], rig[4000010], seg2[4000010], n_cnt;

int query2(int v, int L, int R, int QL, int QR){
	if (seg2[v] == 0)
		return 0;
	if (QR < L || R < QL)
		return 0;
	if (QL <= L && R <= QR)
		return seg2[v];
	int mid = (L+R)/2;
	int ret = 0;
	if (lef[v] != 0)
		ret += query2(lef[v], L, mid, QL, QR);
	if (rig[v] != 0)
		ret += query2(rig[v], mid+1, R, QL, QR);
	return ret;
}

void update2(int v, int L, int R, int p){
	seg2[v]++;
	if (L == R)
		return;
	int mid = (L+R)/2;
	if (p <= mid){
		if (lef[v] == 0)
			lef[v] = ++n_cnt;
		update2(lef[v], L, mid, p);
	}
	else{
		if (rig[v] == 0)
			rig[v] = ++n_cnt;
		update2(rig[v], mid+1, R, p);
	}
}

int N, K, c1[100010], c2[100010], c[100010];

int query(int v, int L, int R, int QL, int QR, int QL2, int QR2){
	if (QR < L || R < QL) return 0;
	if (QL <= L && R <= QR){
		return query2(v, 1, N, QL2, QR2);
		// return seg[v].order_of_key(QR2+1) - seg[v].order_of_key(QL2);
	}
	int mid = (L+R)/2;
	return query(v*2, L, mid, QL, QR, QL2, QR2) + query(v*2+1, mid+1, R, QL, QR, QL2, QR2);
}
void update(int v, int L, int R, int p, int val){
	update2(v, 1, N, val);
	if (L == R)
		return;
	int mid = (L+R)/2;
	if (p <= mid)
		update(v*2, L, mid, p, val);
	else
		update(v*2+1, mid+1, R, p, val);
}

int main(){
	freopen("friendcross.in","r",stdin);
	freopen("friendcross.out","w",stdout);
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(lef, lef + 4000010, 0);
	fill(rig, rig + 4000010, 0);
	fill(seg2, seg2 + 4000010, 0);
	cin >> N >> K;
	for (int i=1; i<=N; ++i){
		int x;
		cin >> x;
		c1[x] = i;
	}
	for (int i=1; i<=N; ++i){
		int x;
		cin >> x;
		c[i] = x;
		c2[i] = c1[x];
	}
	n_cnt = N*4;
	int ans = 0;
	for (int i=1; i<=N; ++i){
		ans += query(1, 1, N, c2[i]+1, N, 1, N) - query(1, 1, N, c2[i]+1, N, c[i] - K, c[i] + K);
		update(1, 1, N, c2[i], c[i]);
	}
	cout << ans;

	return 0;
}