#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cout << '>' << #x << ": " << x << endl
typedef long long lint;

struct SegmentTree{
	lint seg[1010];
	void reset(){memset(seg, 0, sizeof(seg));}
	void update(lint v, lint L, lint R, lint p, lint val){
		if (L == R){
			seg[v] = max(seg[v], val);
			return;
		}
		if (p <= (L+R)/2) update(v*2, L, (L+R)/2, p, val);
		else update(v*2+1, (L+R)/2+1, R, p, val);
		seg[v] = max(seg[v*2], seg[v*2+1]);
	}
	lint query(lint v, lint L, lint R, lint QL, lint QR){
		if (QR < L || R < QL) return -1e9;
		if (QL <= L && R <= QR) return seg[v];
		return max(query(v*2, L, (L+R)/2, QL, QR), query(v*2+1, (L+R)/2+1, R, QL, QR));
	}
}root[310];

struct Rect{
	short r1, c1, r2, c2;
	Rect(int _r1, int _c1, int _r2, int _c2){r1 = _r1, c1 = _c1, r2 = _r2, c2 = _c2;}
	bool operator < (const Rect &a) const{
		if (c2 != a.c2) return c2 < a.c2;
		return r2 < a.r2;
	}
};


short n, g[310][310];
short dp[310][310];
lint marea[310][310];

bool isempty(lint r, lint i, lint j){
	return (g[r][j] - g[r][i-1]) == 0;
}

lint area(Rect x){
	return (lint)(x.r2 - x.r1 - 1)*(x.c2 - x.c1 - 1);

}

int main(){
	freopen("test.txt","r",stdin);
	// freopen("eight.in","r",stdin);
	// freopen("eight.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	memset(dp, 0, sizeof(dp));
	cin >> n;
	for (lint i=1; i<=n; ++i){
		for (lint j=1; j<=n; ++j){
			char ch; cin >> ch;
			g[i][j] = (ch == '*')?1:0;
			g[i][j] += g[i][j-1];
		}
	}
	lint ans = 0;
	for (int j=3; j<=n; ++j){
		for (lint r = 1; r <= n; ++r){
			for (lint i=j-2; i>=1; --i){
				if (!isempty(r, i, i) || !isempty(r, j, j)){
					dp[r][i] = 0;
				}
				else if (dp[r-1][i] == 0){
					dp[r][i] = isempty(r, i, j)?1:0;
				}
				else{
					dp[r][i] = dp[r-1][i] + 1;
				}
				if (isempty(r, i, j)){
					if (dp[r][i] > 2){
						int r1 = r-dp[r][i]+1, c1 = i, r2 = r, c2 = j;
						root[r2].update(1, 1, n, c1, area(Rect(r1, c1, r2, c2)));
					}
				}
			}
		}

		for (lint r = n; r >= 1; --r){
			for (lint i=j-2; i>=1; --i){
				if (!isempty(r, i, i) || !isempty(r, j, j)){
					dp[r][i] = 0;
				}
				else if (dp[r+1][i] == 0){
					dp[r][i] = isempty(r, i, j)?1:0;
				}
				else{
					dp[r][i] = dp[r+1][i] + 1;
				}
				if (isempty(r, i, j)){
					if (dp[r][i] > 2){
						int r2 = r+dp[r][i]-1, c2 = j, r1 = r, c1 = i;
						ans = max(ans, area(Rect(r1, c1, r2, c2))*root[r1].query(1, 1, n, c1, c2));
					}
				}
			}
		}

	}
	if (ans == 0) ans = -1;
	cout << ans;
	return 0;
}