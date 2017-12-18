#include <bits/stdc++.h>

using namespace std;

struct Node{
	int sum = 0, minpre = 0;
} seg[400010];

void update(int v, int L, int R, int p, int val){
	if (L == R){
		seg[v].sum += val;
		seg[v].minpre = min(0, seg[v].sum);
		return;
	}
	int mid = (L+R)/2;
	if (p <= mid)
		update(v*2, L, mid, p, val);
	else
		update(v*2+1, mid+1, R, p, val);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
	seg[v].minpre = min(seg[v*2].minpre, seg[v*2].sum + seg[v*2+1].minpre);
}
int N, bins[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i=1; i<=N; ++i){
		cin >> bins[i];
	}
	int ans = 0;
	for (int i=1; i<=N/2; ++i){
		update(1, 1, N, bins[i], -2);
		update(1, 1, N, bins[i*2-1], 1);
		update(1, 1, N, bins[i*2], 1);
		if (seg[1].minpre >= 0)
			ans = i;
	}
	cout << ans;

	return 0;
}