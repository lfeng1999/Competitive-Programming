#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;
int a, b, n, nc, arr[500010], toadd;

struct SegmentTree{
	int cval[1200010], rcval[1200010], lcval[1200010];
	int lazy[1200010];

	void build_tree(int v, int L, int R){
		lazy[v] = inf;
		if (L == R){
			rcval[v] = lcval[v] = arr[L];
			cval[v] = 1;
			return;
		}
		build_tree(v*2, L, (L+R)/2);
		build_tree(v*2+1, (L+R)/2+1, R);
		cval[v] = cval[v*2] + cval[v*2+1];
		if (rcval[v*2] == lcval[v*2+1]) cval[v]--;
		rcval[v] = rcval[v*2+1];
		lcval[v] = lcval[v*2];
	}

	void push_lazy(int v){
		if (lazy[v] == inf) return;
		cval[v] = 1; rcval[v] = lcval[v] = lazy[v];
		if (v*2 < 1200000){
			lazy[v*2] = lazy[v*2+1] = lazy[v];
		}
		lazy[v] = inf;
	}

	int querycol(int v, int L, int R, int p){
		push_lazy(v);
		if (L == R) return lcval[v];
		if (p <= (L+R)/2) return querycol(v*2, L, (L+R)/2, p);
		else return querycol(v*2+1, (L+R)/2+1, R, p);
	}

	void updateval(int v, int L, int R, int p, int nval){
		push_lazy(v);
		if (L == R){
			lcval[v] = rcval[v] = nval;
			cval[v] = 1;
			return;
		}
		if (p <= (L+R)/2) updateval(v*2, L, (L+R)/2, p, nval);
		else updateval(v*2+1, (L+R)/2+1, R, p, nval);
		push_lazy(v*2); push_lazy(v*2+1);
		cval[v] = cval[v*2] + cval[v*2+1];
		if (rcval[v*2] == lcval[v*2+1]) cval[v]--;
		rcval[v] = rcval[v*2+1];
		lcval[v] = lcval[v*2];
	}

	int queryrange(int v, int L, int R, int QL, int QR){
		push_lazy(v);
		if (QL <= L && R <= QR){
			return cval[v];
		}
		int ret = 0;
		if (QL <= (L+R)/2 && (L+R)/2 + 1 <= QR){
			ret = queryrange(v*2, L, (L+R)/2, QL, QR) + queryrange(v*2+1, (L+R)/2+1, R, QL, QR);
			if (rcval[v*2] == lcval[v*2+1]) ret--; 
			return ret;
		}
		else if (QL <= (L+R)/2){
			return queryrange(v*2, L, (L+R)/2, QL, QR);
		}
		else{
			return queryrange(v*2+1, (L+R)/2+1, R, QL, QR);
		}
	}

	void updaterange(int v, int L, int R, int UL, int UR, int nval){
		push_lazy(v);
		if (UL <= L && R <= UR){
			lazy[v] = nval;
			return;
		}
		if (UL <= (L+R)/2) updaterange(v*2, L, (L+R)/2, UL, UR, nval);
		if ((L+R)/2+1 <= UR) updaterange(v*2+1, (L+R)/2 + 1, R, UL, UR, nval);
		push_lazy(v*2); push_lazy(v*2+1);
		cval[v] = cval[v*2] + cval[v*2+1];
		if (rcval[v*2] == lcval[v*2+1]) cval[v]--;
		rcval[v] = rcval[v*2+1];
		lcval[v] = lcval[v*2];
	}
} seg;

int get_pos(int y){
	int ret = (y - b)/a;
	return (ret + toadd)%n;
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nc;
	toadd = (1e9)/n;
	toadd *= n;
	for (int i=0; i<n; ++i){
		cin >> arr[i];
	}
	int nq;
	cin >> nq;
	a = 1; b = 0;
	seg.build_tree(1, 0, n-1);
	for (int qq=0; qq<nq; ++qq){
		string cmd;
		cin >> cmd;
		if (cmd == "R"){
			int k; cin >> k;
			b += k;
		}
		else if (cmd == "F"){
			a *= -1;
			b *= -1;
		}
		else if (cmd == "S"){
			//seg update
			int i, j;
			cin >> i >> j;
			--i; --j;
			i = get_pos(i);
			j = get_pos(j);
			int val1 = seg.querycol(1, 0, n-1, i);
			int val2 = seg.querycol(1, 0, n-1, j);
			seg.updateval(1, 0, n-1, i, val2);
			seg.updateval(1, 0, n-1, j, val1);
		}
		else if (cmd == "P"){
			//paint, seg update
			int i, j, col;
			cin >> i >> j >> col;
			--i; --j;
			i = get_pos(i);
			j = get_pos(j);
			if (a < 0) swap(i, j);
			if (i > j){
				seg.updaterange(1, 0, n-1, i, n-1, col);
				seg.updaterange(1, 0, n-1, 0, j, col);
			}
			else
				seg.updaterange(1, 0, n-1, i, j, col);
		}
		else if (cmd == "C"){
			//count, seg query
			int ans = seg.queryrange(1, 0, n-1, 0, n-1);
			int val1 = seg.querycol(1, 0, n-1, 0);
			int val2 = seg.querycol(1, 0, n-1, n-1);
			if (ans != 1 && val1 == val2) ans--;
			cout << ans << '\n';
		}
		else if (cmd == "CS"){
			//count, seq query
			int i, j;
			cin >> i >> j;
			--i; --j;
			i = get_pos(i);
			j = get_pos(j);
			if (a < 0) swap(i, j);

			int ans;

			if (i > j){
				ans = seg.queryrange(1, 0, n-1, i, n-1) + seg.queryrange(1, 0, n-1, 0, j);
				if (seg.querycol(1, 0, n-1, 0) == seg.querycol(1, 0, n-1, n-1)) ans--;
			}
			else
				ans = seg.queryrange(1, 0, n-1, i, j);


			//check
			cout << ans << '\n';
		}
	}
	return 0;
}