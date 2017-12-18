#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int btype, n, md, maxx;

struct BIT2{
	int bit[150010];
	BIT2(){
		memset(bit, 0, sizeof(bit));
	}
	int query(int i){
		i = max(i, 0);
		i = min(i, 150000);
		int ret = 0;
		for (; i > 0; i -= i&(-i)){
			ret += bit[i];
		}
		return ret;
	}
	void update(int i, int val){
		for (; i < 150010; i += i&(-i)) bit[i] += val;
	}
};
bool diagsort(pair<int,int> &a, pair<int,int> &b){
	return a.first - a.second < b.first - b.second;
}

int main(){
	freopen("test2.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> btype >> n >> md >> maxx;
	if (btype == 1){
		vector<int> V;
		for (int qq=0; qq<n; ++qq){
			int x; cin >> x; V.push_back(x);
		}
		sort(V.begin(), V.end());
		lint ans = 0;
		for (int x : V){
			// cout << x << " " << upper_bound(V.begin(), V.end(), x + md) - upper_bound(V.begin(), V.end(), x - md - 1) << endl;
			ans += upper_bound(V.begin(), V.end(), x + md) - upper_bound(V.begin(), V.end(), x - md - 1) - 1;
		}
		cout << ans/2;
	}
	else if (btype == 2){
		if (n > 20000) return 0;
		vector<pair<int,int>> ps;
		int ans = 0;
		for (int qq=0; qq<n; ++qq){
			int x, y; cin >> x >> y;
			for (auto it : ps){
				if (abs(it.first - x) + abs(it.second - y) <= md){
					ans++;
				}
			}
			ps.push_back({x, y});
		}
		cout << ans;
	}
	else{
		vector<pair<int,pair<int,int>>> V;
		int ans = 0;
		for (int qq=0; qq<n; ++qq){
			int a, b, c; cin >> a >> b >> c;
			for (auto it : V){
				if (abs(it.first - a) + abs(it.second.first - b) + abs(it.second.second - c) <= md){
					ans++;
				}
			}
			V.push_back({a, {b,c}});
		}
		cout << ans;

	}
	return 0;
}