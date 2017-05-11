#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
struct Node{
	lint sum, dif;
} seg[270010];

lint cow[100010][2], n, nq, skipdif[100010], distto[100010];

lint dist(lint i, lint j){
	return abs(cow[i][0] - cow[j][0]) + abs(cow[i][1] - cow[j][1]);
}


void build_tree(lint v, lint L, lint R){
	if (L == R){
		seg[v].sum = distto[L];
		seg[v].dif = skipdif[L];
		return;
	}
	build_tree(v*2, L, (L+R)/2);
	build_tree(v*2+1, (L+R)/2 + 1, R);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
	seg[v].dif = max(seg[v*2].dif, seg[v*2+1].dif);
}
void update(lint v, lint L, lint R, lint p){
	if (L == R){
		seg[v].sum = distto[L]; seg[v].dif = skipdif[L]; return;
	}
	if (p <= (L+R)/2) update(v*2, L, (L+R)/2, p);
	else update(v*2+1, (L+R)/2 + 1, R, p);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
	seg[v].dif = max(seg[v*2].dif, seg[v*2+1].dif);
}
lint querysum(lint v, lint L, lint R, lint QL, lint QR){
	if (R < QL || QR < L) return 0;
	if (QL <= L && R <= QR) return seg[v].sum;
	return querysum(v*2, L, (L+R)/2, QL, QR) + querysum(v*2+1, (L+R)/2 + 1, R, QL, QR);

}
lint querydif(lint v, lint L, lint R, lint QL, lint QR){
	if (L > R) return 0;
	if (R < QL || QR < L) return -1e9;
	if (QL <= L && R <= QR) return seg[v].dif;
	return max(querydif(v*2, L, (L+R)/2, QL, QR), querydif(v*2+1, (L+R)/2+1, R, QL, QR));
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("marathon.in","r",stdin);
	freopen("marathon.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nq;
	for (lint i=1; i<=n; ++i){
		cin >> cow[i][0] >> cow[i][1];
	}
	for (lint i=2; i<=n; ++i){
		distto[i] = dist(i-1, i);
	}
	for (lint i=2; i<=n-1; ++i){
		skipdif[i] = dist(i-1, i) + dist(i, i+1) - dist(i-1, i+1);
	}
	build_tree(1, 1, n);
	for (lint qq=0; qq<nq; ++qq){
		char ch; cin >> ch;
		if (ch == 'U'){
			lint p; cin >> p;
			cin >> cow[p][0] >> cow[p][1];
			distto[p] = dist(p-1, p);
			skipdif[p] = dist(p-1, p) + dist(p, p+1) - dist(p-1, p+1);				
			update(1, 1, n, p);
			if (p >= 2){
				skipdif[p-1] = dist(p-2, p-1) + dist(p-1, p) - dist(p-2, p);
				update(1, 1, n, p-1);
			}
			if (p <= n-1){
				distto[p+1] = dist(p, p+1);
				skipdif[p+1] = dist(p, p+1) + dist(p+1, p+2) - dist(p, p+2);
				update(1, 1, n, p+1);
			}
		}
		else if (ch == 'Q'){
			lint L, R; cin >> L >> R;
			cout << querysum(1, 1, n, L+1, R) - querydif(1, 1, n, L+1, R-1) << '\n';
		}
	}
	return 0;
}