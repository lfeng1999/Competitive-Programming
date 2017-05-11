#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
struct Node{
	lint lazy, L, R;
	lint val, mval = 1e9;
} seg[540010];

int n, nq, bales[200010];
void build_tree(int v, int L, int R){
	seg[v].L = L; seg[v].R = R;
	if (L == R){
		seg[v].val = seg[v].mval = bales[L];
		seg[v].lazy = 0;
		return;
	}
	int mid = (L+R)/2;
	build_tree(v*2, L, mid);
	build_tree(v*2+1, mid+1, R);
	seg[v].val = seg[v*2].val + seg[v*2+1].val;
	seg[v].mval = min(seg[v*2].mval, seg[v*2+1].mval);
}
void push_lazy(int v){
	int L = seg[v].L, R = seg[v].R;
	if (v*2 < 540000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].val += seg[v].lazy * (R-L+1);
	seg[v].mval += seg[v].lazy;
	seg[v].lazy = 0;
}
void update(int v, int UL, int UR, int c){
	int L = seg[v].L, R = seg[v].R;
	push_lazy(v);
	if (R < UL || UR < L) return;
	if (UL <= L && R <= UR){
		seg[v].lazy += c;
		push_lazy(v);
		return;
	}
	update(v*2, UL, UR, c);
	update(v*2+1, UL, UR, c);
	seg[v].mval = min(seg[v*2].mval, seg[v*2+1].mval);
	seg[v].val = seg[v*2].val + seg[v*2+1].val;
}

lint query3(int v, int QL, int QR){
	int L = seg[v].L, R = seg[v].R;
	push_lazy(v);
	if (QR < L || R < QL) return 0;	
	if (QL <= L && R <= QR){
		return seg[v].val;
	}
	return query3(v*2, QL, QR) + query3(v*2+1, QL, QR);
}

lint query2(int v, int QL, int QR){
	int L = seg[v].L, R = seg[v].R;
	push_lazy(v);
	if (QR < L || R < QL) return 1e18;
	if (QL <= L  && R <= QR) return seg[v].mval;
	return min(query2(v*2, QL, QR), query2(v*2+1, QL, QR));
}


int main(){
	// freopen("test.txt","r",stdin);
	freopen("haybales.in","r",stdin);
	freopen("haybales.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nq;
	for (int i=1; i<=n; ++i){
		cin >> bales[i];
	}
	build_tree(1, 1, n);
	for (int qq=0; qq<nq; ++qq){
		char ch; cin >> ch;
		int L, R; cin >> L >> R;
		if (ch == 'M'){
			cout << query2(1, L, R) << '\n';
		}
		else if (ch == 'S'){
			cout << query3(1, L, R) << '\n';
		}
		else{
			int x; cin >> x;
			update(1, L, R, x);
		}
	}

	return 0;
}