#include <bits/stdc++.h> //Make SegTrees on an array.... is the best way++++++

using namespace std;

typedef long long lint;
const int SEGCOUNT2 = 18000010;
int seg2[SEGCOUNT2];
int N, K, lef[SEGCOUNT2], rig[SEGCOUNT2];
int scnt = 270000;

void update2(int v, int L, int R, int p, int val){
	seg2[v] += val;
	if (L == R){
		return;
	}
	int mid = (L+R)/2;
	if (p <= mid){
		if (lef[v] == 0) lef[v] = ++scnt;
		update2(lef[v], L, mid, p, val);
	}
	else{
		if (rig[v] == 0) rig[v] = ++scnt;
		update2(rig[v], mid+1, R, p, val);
	}
}

void update(int v, int L, int R, int p1, int p2, int val){
	update2(v, 1, N, p2, val);
	if (L == R) return;
	int mid = (L+R)/2;
	if (p1 <= mid)
		update(v*2, L, mid, p1, p2, val);
	else
		update(v*2+1, mid+1, R, p1, p2, val);
}

int query2(int v, int L, int R, int QL, int QR){
	if (QL <= L && R <= QR) return seg2[v];
	int mid = (L+R)/2;
	int ret = 0;
	if (QL <= mid && lef[v]) ret += query2(lef[v], L, mid, QL, QR);
	if (mid+1 <= QR && rig[v]) ret += query2(rig[v], mid+1, R, QL, QR);
	return ret;
}

int query(int v, int L, int R, int QL, int QR, int QL2, int QR2){
	if (QR < L || R < QL) return 0;

	if (QL <= L && R <= QR){
		return query2(v, 1, N, QL2, QR2);
	}
	int mid = (L+R)/2;
	return query(v*2, L, mid, QL, QR, QL2, QR2) + query(v*2+1, mid+1, R, QL, QR, QL2, QR2);
}

pair<int,int> cows[100010];

int main(){
	// freopen("test.txt", "r", stdin);
	freopen("friendcross.in","r",stdin);
	freopen("friendcross.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		cows[x].first = i;
	}
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		cows[x].second = i;
	}
	lint ans = 0;
	for (int i=K+1; i<=N; ++i){
		update(1, 1, N, cows[i].first, cows[i].second, 1);
	}
	for (int i=1; i<=N-K; ++i){
		update(1, 1, N, cows[i+K].first, cows[i+K].second, -1);

		// THESE 2 ways to query are the same.... This one might be faster >>> 
		int RR = query(1, 1, N, 1, N, 1, cows[i].second); //LOGN
		int UU = query(1, 1, N, 1, cows[i].first, 1, N); //LOGN
		int NN = query(1, 1, N, 1, cows[i].first, 1, cows[i].second); //(LOGN)^2
		ans += RR + UU - 2*NN;
		// ans += query(1, 1, N, 1, cows[i].first, cows[i].second, N) + query(1, 1, N, cows[i].first, N, 1, cows[i].second);
		// This is 2*(LOGN)^2 fucking constants
	}
	cout << ans;
	return 0;
}