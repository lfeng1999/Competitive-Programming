#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct Dirt{
	int h, typ, pos;
	bool operator < (const Dirt &a) const{
		if (h != a.h) return h < a.h;
		return pos < a.pos;
	}
} d[1000010], tmp[1000010];

int N, Z, n = 0;
lint X, Y;
int arr[1000010], pos[1000010], typ[1000010];
lint dp[1000010][2], dp2[1000010][2];
lint solve(int beg, int ed){
	
	for (int i = beg; i<=ed; ++i){
		tmp[i-beg+1] = d[i];
	}
	ed = ed - beg + 1;
	beg = 1;

	dp[1][1] = dp[0][0] = dp[0][1] = 0;
	for (int i=2; i<=ed; ++i){
		if (i%2 == 1){
			dp[i][1] = min(dp[i-2][1] + Z*(tmp[i].pos - tmp[i-1].pos), dp[i-1][0]);
		}
		else{
			dp[i][0] = min(dp[i-2][0] + Z*(tmp[i].pos - tmp[i-1].pos), dp[i-1][1] + X + Y);
		}
	}


	if (ed % 2 == 0) return dp[ed][0];
	dp2[ed + 1][0] = dp2[ed+1][1] = dp2[ed][1] = 0;
	for (int i=ed-1; i>=1; --i){ //ed is odd #
		if (i%2 == 1){ //means odd # behind it
			dp2[i][1] = min(dp2[i+2][1] + Z*(tmp[i+1].pos - tmp[i].pos), dp2[i+1][0]);
		}
		else{
			dp2[i][0] = min(dp2[i+2][0] + Z*(tmp[i+1].pos - tmp[i].pos), dp2[i+1][1] + X + Y);
		}
	}

	lint ret = 1e18;
	lint add = (tmp[1].typ > 0)?Y:X;
	for (int i=1;i<=ed; i+=2){
		ret = min(ret, dp[i-1][0] + dp2[i+1][0] + add);
	}


	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("landscape.in","r",stdin);
	freopen("landscape.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> X >> Y >> Z;
	for (int i=1; i<=N; ++i){
		int a, b; cin >> a >> b;
		int dif = abs(a - b);
		for (int j=0; j<dif; ++j){
			typ[++n] = (a > b)?1:-1;
			if (typ[n-1] != typ[n]){
				arr[n] = 0;
			}
			else
				arr[n] = (a > b)?1:-1;
			pos[n] = i;
		}
	}
	for (int i=1; i<=n; ++i){
		arr[i] += arr[i-1];
		d[i].h = arr[i]; d[i].typ = typ[i]; d[i].pos = pos[i];
	}
	sort(d+1, d+1+n);
	int beg = 1, ed = 1;
	lint ans = 0;
	while (beg <= n){
		while (ed <= n && d[ed].h == d[beg].h){
			ed++;
		}
		ans += solve(beg, ed-1);
		beg = ed;
	}
	cout << ans;

	return 0;
}