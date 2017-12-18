#include <bits/stdc++.h>

using namespace std;

int bit[100010], N, boxes[100010];

int query(int i){
	int tot = 0;
	for (; i > 0; i -= i&(-i))
		tot += bit[i];
	return tot;
}

void update(int i, int val){
	for (; i < 100010; i += i&(-i))
		bit[i] += val;
}

struct Node{
	int val = (int)1e9, lazy = 0;
} seg[400010];

void push_lazy(int v){
	seg[v].val += seg[v].lazy;
	if (v*2 < 400010){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;
}

void updatel(int v, int L, int R, int p, int val){
	push_lazy(v);
	if (L == R){
		seg[v].val = val;
		return;
	}
	int mid = (L+R)/2;
	if (p <= mid){
		updatel(v*2, L, mid, p, val);
	}
	else{
		updatel(v*2+1, mid+1, R, p, val);
	}
	push_lazy(v*2);
	push_lazy(v*2+1);
	seg[v].val = min(seg[v*2].val, seg[v*2+1].val);
}

void updater(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v);
	if (UL <= L && R <= UR){
		seg[v].val += val;
		if (v*2 < 400010){
			seg[v*2].lazy += val;
			seg[v*2+1].lazy += val;
		}
		return;
	}
	int mid = (L+R)/2;
	if (UL <= mid){
		updater(v*2, L, mid, UL, UR, val);
	}
	if (mid+1 <= UR){
		updater(v*2+1, mid+1, R, UL, UR, val);
	}
	push_lazy(v*2);
	push_lazy(v*2+1);
	seg[v].val = min(seg[v*2].val, seg[v*2+1].val);
}



int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=1; i<=N; ++i){
		cin >> boxes[i];
	}
	int ans = 0;
	update(boxes[1], -1);
	updatel(1, 1, N, boxes[1], query(boxes[1]));
	updater(1, 1, N, boxes[1]+1, N, -1);
	update(boxes[2], 1);
	updatel(1, 1, N, boxes[2], query(boxes[2]));
	updater(1, 1, N, boxes[2]+1, N, 1);
	if (seg[1].val >= 0)
		ans = 1;
	for (int i=2; i<=N/2; ++i){
		update(boxes[i], -2);
		updater(1, 1, N, boxes[i], N, -2);
		update(boxes[i*2-1], 1);
		updatel(1, 1, N, boxes[i*2-1], query(boxes[i*2-1]));
		updater(1, 1, N, boxes[i*2-1]+1, N, 1);
		update(boxes[i*2], 1);
		updatel(1, 1, N, boxes[i*2], query(boxes[i*2]));
		updater(1, 1, N, boxes[i*2]+1, N, 1);
		if (seg[1].val >= 0)
			ans = i;
	}
	cout << ans;


	return 0;
}