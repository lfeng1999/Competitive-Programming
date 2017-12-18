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
struct BIT3{
	int bit[230][230][230];
	BIT3(){
		memset(bit, 0, sizeof(bit));
	}
	int query(int i, int j, int k){
		i += 75; j += 75; k += 75;
		i = max(i, 0); j = max(j, 0); k = max(k, 0);
		i = min(i, 225); j = min(j, 225); k = min(k, 225);
		int ret = 0;
		for (int i2=i; i2 > 0; i2 -= i2&(-i2)){
			for (int j2=j; j2 > 0; j2 -= j2&(-j2)){
				for (int k2=k; k2 > 0; k2 -= k2&(-k2)){
					ret += bit[i2][j2][k2];
				}
			}
		}
		return ret;
	}
	void update(int i2, int j2, int k2, int val){
		i2 += 75; j2 += 75; k2 += 75;
		for (int i=i2; i < 230; i += i&(-i)){
			for (int j=j2; j<230; j+=j&(-j)){
				for (int k=k2; k<230; k += k&(-k)){
					bit[i][j][k] += val;
				}
			}
		}
	}
} bit3;
bool diagsort(pair<int,int> &a, pair<int,int> &b){
	return a.first - a.second < b.first - b.second;
}
int triplesum(pair<int,pair<int,int>> &p){
	return p.first + p.second.first + p.second.second;
}
bool sort3(pair<int,pair<int,int>> &a, pair<int,pair<int,int>> &b){
	return triplesum(a) < triplesum(b);
}

int main(){
	// freopen("test2.txt","r",stdin);
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
			ans += upper_bound(V.begin(), V.end(), x + md) - upper_bound(V.begin(), V.end(), x - md - 1) - 1;
		}
		cout << ans/2;
	}
	else if (btype == 2){
		vector<pair<int,int>> ps;
		BIT2 bit = BIT2();
		for (int qq=0; qq<n; ++qq){
			int x, y; cin >> x >> y;
			ps.push_back({x, y});
		}
		sort(ps.begin(), ps.end(), diagsort);
		int j = 0, l = 0;
		lint ans = 0;
		for (int k=0; k<n; ++k){
			if (k+1 < n && ps[k].first - ps[k].second == ps[k+1].first - ps[k+1].second) continue;
			while (l < n && ps[l].first - ps[l].second <= ps[k].first - ps[k].second + md){
				bit.update(ps[l].first + ps[l].second, 1);
				++l;
			}
			for (int i=j; i<=k; ++i){
				bit.update(ps[i].first + ps[i].second, -1);
			}
			vector<int> tmp;
			for (int i = j; i<=k; ++i){
				tmp.push_back(ps[i].first + ps[i].second);
			}
			sort(tmp.begin(), tmp.end());
			int tmpans = 0;
			for (int i=j; i<=k; ++i){
				tmpans += upper_bound(tmp.begin(), tmp.end(), ps[i].first + ps[i].second + md) - lower_bound(tmp.begin(), tmp.end(), ps[i].first + ps[i].second - md) - 1;
			}
			tmpans/=2;
			ans += tmpans;
			for (int i=j; i<=k; ++i){
				ans += bit.query(ps[i].first + ps[i].second + md);
				ans -= bit.query(ps[i].first + ps[i].second - md - 1);
			}
			j = k + 1;
		}
		cout << ans;
	}
	else if (btype == 3){
		vector<pair<int,pair<int,int>>> ps;

		for (int qq=0; qq<n; ++qq){
			int x, y, z; cin >> x >> y >> z;
			ps.push_back({x, {y, z}});
		}
		sort(ps.begin(), ps.end(), sort3);
		lint ans = 0;
		int j=0, l=0;
		for (int k=0; k<n; ++k){
			while (l < n && triplesum(ps[l]) <= triplesum(ps[k]) + md){
				int x = ps[l].first, y = ps[l].second.first, z = ps[l].second.second;
				bit3.update(-x+y+z, x-y+z, x+y-z, 1);
				++l;
			}
			while (j < n && triplesum(ps[j]) + md < triplesum(ps[k])){
				int x = ps[j].first, y = ps[j].second.first, z = ps[j].second.second;
				bit3.update(-x+y+z, x-y+z, x+y-z, -1);
				++j;
			}
			int x = ps[k].first, y = ps[k].second.first, z = ps[k].second.second;
			ans += bit3.query(-x+y+z + md, x-y+z + md, x+y-z + md);
			
			ans -= bit3.query(-x+y+z - md - 1, x-y+z + md, x+y-z + md);
			ans -= bit3.query(-x+y+z + md, x-y+z - md - 1, x+y-z + md);
			ans -= bit3.query(-x+y+z + md, x-y+z + md, x+y-z - md - 1);
			
			ans += bit3.query(-x+y+z - md - 1, x-y+z - md - 1, x+y-z + md);
			ans += bit3.query(-x+y+z - md - 1, x-y+z + md, x+y-z - md - 1);
			ans += bit3.query(-x+y+z + md, x-y+z - md - 1, x+y-z - md - 1);
			
			ans -= bit3.query(-x+y+z - md - 1, x-y+z - md - 1, x+y-z - md - 1);
		}
		ans -= n;
		ans /= 2;
		cout << ans;
	}
	return 0;
}