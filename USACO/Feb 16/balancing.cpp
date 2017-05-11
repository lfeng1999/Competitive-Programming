#include <bits/stdc++.h>

using namespace std;

struct BIT{
	int bit[1000010], tot;
	void update(int i, int val){
		tot += val;
		for (; i < 1000010; i += i&(-i))
			bit[i] += val;
	}
	int query(int i){
		int ret = 0;
		for (; i > 0; i -=i&(-i))
			ret += bit[i];
		return ret;
	}
} bitl, bitr;

int solve(){
	int L = 0, R = 1048576;
	while (R - L != 2){
		int mid = (L+R)/2;
		int q3 = bitl.query(mid), q2 = bitl.tot - q3;
		int q4 = bitr.query(mid), q1 = bitr.tot - q4;
		int maxbot = max(q3, q4), maxtop = max(q1, q2);
		// cout << q1 << " " << q2 << " " << q3 << " " << q4 << " " << maxbot << " " << maxtop << endl;
		if (R - L == 4){
			return max(maxbot, maxtop);
		}

		if (maxbot < maxtop){
			L = mid;
		}
		else if (maxbot > maxtop){
			R = mid;
		}
		else if (maxbot == maxtop){
			return maxbot;
		}
	}
	return 1e9; //lol
}

int n;
vector<pair<int,int>> pts;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("balancing.in","r",stdin);
	freopen("balancing.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		int x, y; cin >> x >> y;
		pts.push_back(make_pair(x, y));
	}
	sort(pts.begin(), pts.end());
	reverse(pts.begin(), pts.end());
	for (int i=0; i<pts.size(); ++i){
		bitr.update(pts[i].second, 1);
	}
	int curx = 0, best = 1e9;
	while (!pts.empty()){
		curx = pts.back().first;
		while (!pts.empty() && pts.back().first == curx){
			bitr.update(pts.back().second, -1);
			bitl.update(pts.back().second, 1);
			// cout << "LMAO";
			pts.pop_back();
		}
		best = min(best, solve());
	}
	cout << best;
	return 0;
}