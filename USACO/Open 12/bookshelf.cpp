#include <bits/stdc++.h>

using namespace std;


int bw[100010], bh[100010], n, maxlen, pre[100010];
struct SegmentTree{
	int seg[270010], lazy[270010], lazyseg[270010];
	void reset(){fill(lazy, lazy+270010, -1);memset(seg, 0, sizeof(seg));}
	void push_lazy(int v){
		if (lazy[v] == -1) return;
		lazyseg[v] = seg[v] + lazy[v];
		if (v*2 < 270010){
			lazy[v*2] = lazy[v];
			lazy[v*2+1] = lazy[v];
		}
		lazy[v] = -1;
	}
	void updatep(int v, int L, int R, int p, int val){
		push_lazy(v);
		if (R < p || p < L) return;
		if (L == R){
			seg[v] = val;
			lazyseg[v] = val;
			return;
		}
		updatep(v*2, L, (L+R)/2, p, val);
		updatep(v*2+1, (L+R)/2+1, R, p, val);
		seg[v] = min(seg[v*2], seg[v*2+1]);
		lazyseg[v] = min(lazyseg[v*2], lazyseg[v*2+1]);
		// if (v == 260017)
	}
	void updater(int v, int L, int R, int UL, int UR, int val){
		push_lazy(v);
		if (UR < L || R < UL) return;
		if (UL <= L && R <= UR){
			lazy[v] = val;
			push_lazy(v);
			return;
		}
		updater(v*2, L, (L+R)/2, UL, UR, val);
		updater(v*2+1, (L+R)/2+1, R, UL, UR, val);
		seg[v] = min(seg[v*2], seg[v*2+1]);
		lazyseg[v] = min(lazyseg[v*2], lazyseg[v*2+1]);
	}
	int query(int v, int L, int R, int QL, int QR){
		push_lazy(v);
		if (QR < L || R < QL) return 1e9;
		if (QL <= L && R <= QR){
			return lazyseg[v];
		}
		return min(query(v*2, L, (L+R)/2, QL, QR), query(v*2+1, (L+R)/2+1, R, QL, QR));
	}
} seg;


int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	seg.reset();
	cin >> n >> maxlen;
	for (int i=1; i<=n; ++i){
		cin >> bh[i] >> bw[i];
	}
	int len = 0, L = 1;
	for (int R = 1; R <= n; ++R){
		len += bw[R];
		while (len > maxlen){
			len -= bw[L];
			L++;
		}
		pre[R] = L;
	}
	stack<pair<int,int>> stk;
	int ans = 0, fk = 0;
	for (int R = 1; R <= n; ++R){
		int ul = R;
		pair<int,int> toadd = make_pair(bh[R], R);
		while (!stk.empty() && toadd >= stk.top()){
			stk.pop();
		}
		if (!stk.empty()) ul = stk.top().second + 1;
		else ul = 0;
		stk.push(toadd);
		seg.updater(1, 0, n+1, ul, R, bh[R]);
		ans = seg.query(1, 0, n+1, pre[R], R);
		seg.updatep(1, 0, n+1, R+1, ans);
	}
	cout << ans;
	return 0;
}