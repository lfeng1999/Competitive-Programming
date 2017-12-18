#include <bits/stdc++.h>

using namespace std;

int m, d[100010][3], value[100010];

vector<pair<int,int>> upd; 

struct Node{
	int val = 0, lazy = 0;
} seg[400010];

void push_lazy(int v){
	seg[v].val += seg[v].lazy;
	if (v*2 <= 400000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;
}
void update(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v);
	if (UL <= L && R <= UR){
		seg[v].val += val;
		if (v*2 <= 400000){
			seg[v*2].lazy += val;
			seg[v*2+1].lazy += val;
		}
		return;
	}
	int mid = (L+R)/2;
	if (UL <= mid)
		update(v*2, L, mid, UL, UR, val);
	if (mid+1 <= UR)
		update(v*2+1, mid+1, R, UL, UR, val);
	push_lazy(v*2);
	push_lazy(v*2+1);
	seg[v].val = max(seg[v*2].val, seg[v*2+1].val);
}
int query(int v, int L, int R){
	push_lazy(v);
	if (L == R){
		return value[L];
	}
	push_lazy(v*2);
	push_lazy(v*2+1);
	int mid = (L+R)/2;
	if (seg[v*2+1].val > 0)
		return query(v*2+1, mid+1, R);
	else
		return query(v*2, L, mid);
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> m;
	value[0] = -1;
	for (int i=1; i<=m; ++i){
		cin >> d[i][0] >> d[i][1];
		if (d[i][1] == 1){
			cin >> d[i][2];
		}
		if (d[i][1] == 0)
			d[i][1] = -1;
		value[d[i][0]] = d[i][2];
		int t = d[i][1], p = d[i][0];
		update(1, 0, m, 1, p, t);
		cout << query(1, 0, m) << '\n';
	}

	return 0;
}