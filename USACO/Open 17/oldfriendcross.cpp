#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<int> seg[265000];
int N, K, c1[100010], c2[100010], c[100010];

int query(int v, int L, int R, int QL, int QR, int QL2, int QR2){
	if (QR < L || R < QL) return 0;
	if (QL <= L && R <= QR)
		return seg[v].order_of_key(QR2+1) - seg[v].order_of_key(QL2);
	int mid = (L+R)/2;
	return query(v*2, L, mid, QL, QR, QL2, QR2) + query(v*2+1, mid+1, R, QL, QR, QL2, QR2);
}
void update(int v, int L, int R, int p, int val){
	seg[v].insert(val);

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

	int ans = 0;
	for (int i=1; i<=N; ++i){
		ans += query(1, 1, N, c2[i]+1, N, 1, N) - query(1, 1, N, c2[i]+1, N, c[i] - K, c[i] + K);
		update(1, 1, N, c2[i], c[i]);
		// cout << c2[i] << " " << c[i] << " " << ans << " " << query(1, 1, N, c2[i]+1, N, 1, N) << " " << query(1, 1, N, c2[i]+1, N, c[i] - K, c[i] + K) << endl;
	}
	cout << ans;

	return 0;
}
