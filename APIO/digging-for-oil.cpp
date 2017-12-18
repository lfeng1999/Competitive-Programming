#include <bits/stdc++.h>

using namespace std;

#define debug(x) cout << '>' << #x << " : " << x << endl
int nr, nc, len, g[1510][1510], psum[1510][1510], tl[2][1510][1510], tr[2][1510][1510], bl[2][1510][1510], br[2][1510][1510];
int rowup[1510], rowdown[1510], colleft[1510], colright[1510];

int area(int r1, int c1, int r2, int c2){
	return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nr >> nc >> len;
	for (int i=1; i<=nr; ++i){
		for (int j=1; j<=nc; ++j){
			cin >> g[i][j];
			psum[i][j] = g[i][j] + psum[i][j-1] + psum[i-1][j] - psum[i-1][j-1];
		}
	}
	for (int i=len; i<=nr; ++i){
		for (int j=len; j<=nc; ++j){
			tl[0][i][j] = max(max(tl[0][i-1][j], tl[0][i][j-1]), area(i-len+1, j-len+1, i, j));
			if (i >= 2*len || j >= 2*len)
				tl[1][i][j] = max(max(tl[1][i-1][j], tl[1][i][j-1]), max(tl[0][i-len][j], tl[0][i][j-len]) + area(i-len+1, j-len+1, i, j));
			colleft[j] = max(colleft[j], tl[0][i][j]);
			rowup[i] = max(rowup[i], tl[0][i][j]);
		}
	}
	for (int i=nr-len+1; i>=1; --i){
		for (int j=len; j<=nc; ++j){
			bl[0][i][j] = max(max(bl[0][i+1][j], bl[0][i][j-1]), area(i, j-len+1, i+len-1, j));
			if (i >= 2*len || j >= 2*len)
				bl[1][i][j] = max(max(bl[1][i+1][j], bl[1][i][j-1]), max(bl[0][i+len][j], bl[0][i][j-len]) + area(i, j-len+1, i+len-1, j));
		}
	}
	for (int i=len; i<=nr; ++i){
		for (int j=nc-len+1; j>=1; --j){
			tr[0][i][j] = max(max(tr[0][i][j+1], tr[0][i-1][j]), area(i-len+1, j, i, j + len-1));
			if (i >= 2*len || j >= 2*len)
				tr[1][i][j] = max(max(tr[1][i][j+1], tr[1][i-1][j]), max(tr[0][i][j+len], tr[0][i-len][j]) + area(i-len+1, j, i, j + len-1));

		}
	}
	for (int i=nr-len+1; i>=1; --i){
		for (int j=nc-len+1; j>=1; --j){
			br[0][i][j] = max(max(br[0][i+1][j], br[0][i][j+1]), area(i, j, i+len-1, j+len-1));
			if (i >= 2*len || j >= 2*len)
				br[1][i][j] = max(max(br[1][i+1][j], br[1][i][j+1]), max(br[0][i+len][j], br[0][i][j+len]) + area(i, j, i+len-1, j+len-1));
			colright[j] = max(colright[j], br[0][i][j]);
			rowdown[i] = max(rowdown[i], br[0][i][j]);
		}
	}
	int ans = 0;
	for (int i=1; i<=nr; ++i){
		for (int j=1; j<=nc; ++j){
			ans = max(ans, max(tl[1][i][j], tr[1][i][j]) + rowdown[i+1]);
			ans = max(ans, max(tr[1][i][j], br[1][i][j]) + colleft[j-1]);
			ans = max(ans, max(bl[1][i][j], br[1][i][j]) + rowup[i-1]);
			ans = max(ans, max(tl[1][i][j], bl[1][i][j]) + colright[j+1]);
		}
	}
	cout << ans;

	return 0;
}