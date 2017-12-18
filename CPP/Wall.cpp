#include <bits/stdc++.h>

using namespace std;


const int MAXN = 2000010;

struct Node{
	int val = 0, minlazy = -1e9, maxlazy = 1e9;
} seg[MAXN*4];

int N, K,ans[MAXN];

void push_min(int v){
	seg[v].val = max(seg[v].val, seg[v].minlazy);

	if (v*2 < MAXN*4){
		seg[v*2].maxlazy = max(seg[v].minlazy, seg[v*2].maxlazy);
		seg[v*2+1].maxlazy = max(seg[v].minlazy, seg[v*2+1].maxlazy);
		seg[v*2].minlazy = max(seg[v].minlazy, seg[v*2].minlazy);
		seg[v*2+1].minlazy = max(seg[v].minlazy, seg[v*2+1].minlazy);
	}

	seg[v].minlazy = -1e9;
}
void push_max(int v){
	seg[v].val = min(seg[v].val, seg[v].maxlazy);

	if (v*2 < MAXN*4){
		seg[v*2].minlazy = min(seg[v*2].minlazy, seg[v].maxlazy);
		seg[v*2+1].minlazy = min(seg[v*2+1].minlazy, seg[v].maxlazy);
		seg[v*2].maxlazy = min(seg[v*2].maxlazy, seg[v].maxlazy);
		seg[v*2+1].maxlazy = min(seg[v*2+1].maxlazy, seg[v].maxlazy);
	}

	seg[v].maxlazy = 1e9;
}
void push_lazy(int v){
	push_min(v);
	push_max(v);
}

void updatemin(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v);
	if (UR < L || R < UL) return;

	if (UL <= L && R <= UR){
		seg[v].minlazy = max(seg[v].minlazy, val);
		push_lazy(v);
		return;
	}

	int mid = (L+R)/2;
	updatemin(v*2, L, mid, UL, UR, val);
	updatemin(v*2+1, mid+1, R, UL, UR, val);
}
void updatemax(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v);
	if (UR < L || R < UL)
		return;

	if (UL <= L && R <= UR){
		seg[v].maxlazy = min(seg[v].maxlazy, val);
		push_lazy(v);
		return;
	}
	int mid = (L+R)/2;
	updatemax(v*2, L, mid, UL, UR, val);
	updatemax(v*2+1, mid+1, R, UL, UR, val);
}

void expandtree(int v, int L, int R){
	push_lazy(v);
	if (L == R){
		ans[L] = seg[v].val;
		return;
	}
	int mid = (L+R)/2;
	expandtree(v*2, L, mid);
	expandtree(v*2+1, mid+1, R);

}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i=1; i<=K; ++i){
		int op, lef, rig, h;
		cin >> op >> lef >> rig >> h;
		// cout << op << " " << lef << " " << rig << endl;
		if (op == 1)
			updatemin(1, 0, N-1, lef, rig, h);
		else
			updatemax(1, 0, N-1, lef, rig, h);
	}
	expandtree(1, 0, N-1);
	for (int i=0; i<=N-1; ++i){
		cout << ans[i] << "\n";
	}


	return 0;
}