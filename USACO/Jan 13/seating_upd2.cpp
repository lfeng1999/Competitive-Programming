#include <bits/stdc++.h>

using namespace std;

const int MAXSEG = 1200010;

struct SegmentTree{
	int seg[MAXSEG], fl[MAXSEG], fr[MAXSEG], lazy[MAXSEG];
	void build_tree(int v, int L, int R){
		seg[v] = fl[v] = fr[v] = (R-L+1); lazy[v] = -1;
		if (L == R) return;
		build_tree(v*2, L, (L+R)/2); build_tree(v*2+1, (L+R)/2+1, R);
	}
	void push_lazy(int v, int L, int R){
		if (lazy[v] == -1) return;
		if (lazy[v] == 1){ //fill with people
			fl[v] = fr[v] = seg[v] = 0;
		}
		else if (lazy[v] == 2){
			fl[v] = fr[v] = seg[v] = R-L+1;
		}
		if (v*2 < MAXSEG) lazy[v*2] = lazy[v*2+1] = lazy[v];
		lazy[v] = -1;
	}
	void fix(int v, int L, int R){
		int mid = (L+R)/2;
		push_lazy(v*2, L, mid); push_lazy(v*2+1, mid+1, R);
		fl[v] = fl[v*2]; fr[v] = fr[v*2+1];
		if (fl[v*2] == mid-L+1) fl[v] = (mid-L+1)+ fl[v*2+1];
		if (fr[v*2+1] == R-(mid+1)+1) fr[v] = fr[v*2] + R - (mid+1) + 1;
		seg[v] = max(fl[v], fr[v]);
		seg[v] = max(seg[v], max(max(seg[v*2], seg[v*2+1]), fr[v*2] + fl[v*2+1]));
	}
	void update0(int v, int L, int R, int UL, int UR, int typ){ //block off or open
		push_lazy(v, L, R);
		if (UR < L || R < UL){
			return;
		}
		if (UL <= L && R <= UR){
			lazy[v] = typ;//1 means blocked seats, 2 means open seats
			push_lazy(v, L, R);
			return;
		}
		update0(v*2, L, (L+R)/2, UL, UR, typ);
		update0(v*2+1, (L+R)/2+1, R, UL, UR, typ);
		fix(v, L, R);
	}
	void update1(int v, int L, int R, int len){
		push_lazy(v, L, R);
		if (len == 0) return;
		if (R-L+1 == len){
			lazy[v] = 1; push_lazy(v, L, R);
			return;
		}
		int mid = (L+R)/2;
		push_lazy(v*2, L, mid); push_lazy(v*2+1, mid+1, R);
		if (seg[v*2] >= len){
			update1(v*2, L, mid, len);
		}
		else if (fr[v*2] + fl[v*2+1] >= len && fr[v*2]){
			int nl = fr[v*2];
			update0(v*2, L, mid, mid-nl+1, mid, 1);
			update0(v*2+1, mid+1, R, mid+1, mid + len - nl, 1);
		}
		else{
			update1(v*2+1, (L+R)/2+1, R, len);
		}
		fix(v, L, R);
	}
} seg;
int n, m;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("seating.in","r",stdin);
	freopen("seating.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	int ans = 0;
	seg.build_tree(1, 1, n);
	for (int qq=0; qq<m; ++qq){
		char ch; cin >> ch;
		if (ch == 'A'){
			int x; cin >> x;
			if (seg.seg[1] < x){
				ans++;
			}
			else{
				seg.update1(1, 1, n, x);
			}
		}
		else{
			int ul, ur; cin >> ul >> ur;
			seg.update0(1, 1, n, ul, ur, 2);
		}
	}
	cout << ans;
	return 0;
}