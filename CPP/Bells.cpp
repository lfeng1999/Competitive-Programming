#include <bits/stdc++.h>

using namespace std;

int N;

struct Node2{
	Node2 *lef = nullptr, *rig = nullptr;
	int sum = 0;
};
Node2 *seg[265000];

int getsum(Node2 *v){
	if (v)
		return v->sum;
	return 0;
}

void update2(Node2 *root, int L, int R, int p, int val){
	if (L == R){
		root->sum+=val;
		return;
	}
	int mid = (L+R)/2;
	if (p <= mid){
		if (!root->lef)
			root->lef = new Node2();
		update2(root->lef, L, mid, p, val);
	}
	else{
		if (!root->rig)
			root->rig = new Node2();
		update2(root->rig, mid+1, R, p, val);
	}
	root->sum = getsum(root->lef) + getsum(root->rig);
}

void update(int v, int L, int R, int p, int p2, int val){
	if (!seg[v])
		seg[v] = new Node2();
	update2(seg[v], 0, N, p2, val);
	if (L == R)
		return;

	int mid = (L+R)/2;
	if (p <= mid)
		update(v*2, L, mid, p, p2, val);
	else
		update(v*2+1, mid+1, R, p, p2, val);
}

int query2(Node2 *root, int L, int R, int QL, int QR){
	if (!root)
		return 0;
	if (QR < L || R < QL)
		return 0;
	if (QL <= L && R <= QR){
		return root->sum;
	}
	int mid = (L+R)/2;
	return query2(root->lef, L, mid, QL, QR) + query2(root->rig, mid+1, R, QL, QR);
}

int query(int v, int L, int R, int QL, int QR, int QL2, int QR2){
	if (QR < L || R < QL)
		return 0;

	if (QL <= L && R <= QR){
		return query2(seg[v], 0, N, QL2, QR2);
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