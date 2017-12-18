#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int N;
ordered_set<int> seg[265000];

void update(int v, int L, int R, int p, int p2, int val){
	if (val == 1)
		seg[v].insert(p2);
	else
		seg[v].erase(p2);
	// cout << seg[v].size() << endl;
	if (L == R)
		return;

	int mid = (L+R)/2;
	if (p <= mid)
		update(v*2, L, mid, p, p2, val);
	else
		update(v*2+1, mid+1, R, p, p2, val);
}

int query(int v, int L, int R, int QL, int QR, int QL2, int QR2){
	// cout << L << " " << R << " " << QL
	if (QR < L || R < QL)
		return 0;

	if (QL <= L && R <= QR){
		// cout << seg[v].order_of_key(QR2+1) - seg[v].order_of_key(QL2-1) << endl;
		return seg[v].order_of_key(QR2+1) - seg[v].order_of_key(QL2-1);
	}

	int mid = (L+R)/2;

	return query(v*2, L, mid, QL, QR, QL2, QR2) + query(v*2+1, mid+1, R, QL, QR, QL2, QR2);
}


unordered_map<int,int> comp;
set<int> S[1010], unused;
int Q, b[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> Q;
	int cnt = 0;
	for (int i=0; i<=1000; ++i){
		S[i].insert(0);
		S[i].insert(N+1);
		unused.insert(i);
	}
	for (int i=1; i<=N; ++i){
		cin >> b[i];
		int x = b[i];
		if (!comp.count(x)){
			comp[x] = *unused.begin();
			unused.erase(unused.begin());
		}
		x = comp[x];
		auto it = S[x].upper_bound(i);
		auto it2 = it; --it2;
		if (*it != N+1)
			update(1, 1, N+1, *it, *it2, -1);
		update(1, 1, N+1, i, *it2, 1);
		if (*it != N+1)
			update(1, 1, N+1, *it, i, 1);
		S[x].insert(i);
	}
	for (int qq=0; qq<Q; ++qq){
		int t;
		cin >> t;
		if (t == 1){
			int i, f; cin >> i >> f;
			
			//Removing
			int x = b[i];
			x = comp[x];
			S[x].erase(i);
			auto it = S[x].lower_bound(i);
			auto it2 = it; --it2;
			if (*it != N+1)
				update(1, 1, N+1, *it, *it2, 1);
			update(1, 1, N+1, i, *it2, -1);
			if (*it != N+1)
				update(1, 1, N+1, *it, i, -1);
			if (S[x].size() == 2){
				unused.insert(x);
				comp.erase(x);
			}


			b[i] = f;

			//Adding
			x = b[i];
			if (!comp.count(x)){
				comp[x] = *unused.begin();
				unused.erase(unused.begin());
			}
			x = comp[x];
			it = S[x].upper_bound(i);
			it2 = it; --it2;
			if (*it != N+1)
				update(1, 1, N+1, *it, *it2, -1);
			update(1, 1, N+1, i, *it2, 1);
			if (*it != N+1)
				update(1, 1, N+1, *it, i, 1);
			S[x].insert(i);
		}
		else{
			int l, r; cin >> l >> r;
			cout << query(1, 1, N+1, l, r, 0, l-1) << '\n';
		}

	}
	
	return 0;
}