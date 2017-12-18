#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1100000;
struct Node{
	int sum = 0, lazy = 0, maxval = 0;
} seg[MAXN + 10];

unoredered_map<int,int> comp;
int decomp[MAXN];


void push_lazy(int v, int L, int R){
	seg[v].sum = (decomp[R] - decomp[L-1])*seg[v].lazy;
	seg[v].maxval = seg[v].lazy;
	if (v*2 < MAXN){
		seg[v*2].lazy = seg[v].lazy;
		seg[v*2+1].lazy = seg[v].lazy;
	}
	seg[v].lazy = 0;
}

void update(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v, L, R);
	if (R < UL || UR < L)
		return;
	if (UL <= L && R <= UR){
		seg[v].maxval = val;
		seg[v].sum = (decomp[R] - decomp[L-1])*val;
		if (v*2 < MAXN){
			seg[v*2].lazy = seg[v].lazy;
			seg[v*2+1].lazy = seg[v].lazy;
		}
		return;
	}
	int mid = (L+R)/2;
	update(v*2, L, mid, UL, UR, val);
	update(v*2+1, mid+1, R, UL, UR, val);
	seg[v].maxval = max(seg[v*2].maxval, seg[v*2+1].maxval);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
}
int querymax(int v, int L, int R, int UL, int UR){
	push_lazy(v, L, R);
	if (R < UL || UR < L)
		return -1e9;
	if (UL <= L && R <= UR){
		return seg[v].maxval;
	}
	int mid = (L+R)/2;
	return max(querymax(v*2, L, mid, UL, UR), querymax(v*2+1, mid+1, R, UL, UR));
}

int querysum(int v, int L, int R, int UL, int UR){
	push_lazy(v, L, R);
	if (R < UL || UR < L)
		return 0;
	if (UL < L && R <= UR){
		return seg[v].sum;
	}
	else if (UL == L && R == UR){ //WEIRD AF
		return seg[v].sum/(decomp[R] - decomp[L-1]);
	}
	int mid = (L+R)/2;
	return querysum(v*2, L, mid, UL, UR) + querysum(v*2+1, mid+1, R, UL, UR);
}


struct Book{
	int b, e, w;
} b[500010];

int books[500010][3], N;



int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	set<int> S;
	cin >> N;
	for (int i=1; i<=N; ++i){
		cin >> b[i].b >> b[i].e >> b[i].w;
		b[i].e += b[i].b;
		S.insert(b[i].b);
		S.insert(b[i].e);
	}
	int cnt = -1;
	for (int x : S){
		comp[x] = ++cnt;
		decomp[cnt] = x;
	}
	for (int i=1; i<=N; ++i){
		b[i].b = comp[b[i].b];
		b[i].e = comp[b[i].e];
	}
	int ans = 0;
	for (int i=1; i<=N; ++i){
		int l1 = b[i].b, l2 = b[i].e;
		ans += querymax(1, 1, )
	}



	return 0;
}