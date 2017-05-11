#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
struct bit{
	int bit[200010];
	void update(int i, int val){
		i += 100005;
		for (; i < 200010; i += i&(-i)) bit[i] += val;
	}
	int query(int i){
		i += 100005;
		int ret = 0;
		for (; i > 0; i -= i&(-i)) ret += bit[i];
		return ret;
	}
} bit;

int h[100010], n, x;

int main(){
	freopen("test.txt","r",stdin);
	// freopen("median.in","r",stdin);
	// freopen("median.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> x;
	for (int i=1; i<=n; ++i){
		int p; cin >> p;
		h[i] = (p >= x)?1:-1;
	}
	lint ans = 0;
	int tot = 0;
	bit.update(0, 1);
	for (int i=1; i<=n; ++i){
		h[i] += h[i-1];
		ans += bit.query(h[i]);
		bit.update(h[i], 1);
	}
	cout << ans;
	return 0;
}