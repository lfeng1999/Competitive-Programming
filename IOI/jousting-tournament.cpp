#include <bits/stdc++.h>

using namespace std;

int arr[100010];

struct SegmentTree{
	int seg[300010];
	void build_tree(int v, int L, int R){
		if (L == R){
			seg[v] = arr[L];
			return;
		}
		build_tree(v*2, L, (L+R)/2); build_tree(v*2+1, (L+R)/2 + 1, R);
		seg[v] = max(seg[v*2], seg[v*2+1]);
	}
	int querymax(int v, int L, int R, int QL, int QR){
		if (QL <= L && R <= QR) return seg[v];
		int ret = -1;
		if (QL <= (L+R)/2) ret = max(ret, querymax(v*2, L, (L+R)/2, QL, QR));
		if ((L+R)/2 + 1 <= QR) ret = max(ret, querymax(v*2+1, (L+R)/2+1, R, QL, QR));
		return ret;
	}
} maxseg;
struct SegmentTree2{
	int seg[300010];
	void build_tree(int v, int L, int R){
		seg[v] = R - L + 1;
		if (L == R){return;}
		build_tree(v*2, L, (L+R)/2); build_tree(v*2+1, (L+R)/2 + 1, R);
	}
	void update(int v, int L, int R, int UL, int UR){
		if (L == R) {seg[v] = 0; return;}
		if (seg[v] == 0) return;
		if (UL <= (L+R)/2) update(v*2, L, (L+R)/2, UL, UR);
		if ((L+R)/2+1 <= UR) update(v*2 + 1, (L+R)/2+1, R, UL, UR);
		seg[v] = seg[v*2] + seg[v*2+1];
	}
	int query(int v, int L, int R, int val){
		if (L == R) return L;
		if (seg[v*2] >= val) return query(v*2, L, (L+R)/2, val);
		else return query(v*2+1, (L+R)/2+1, R, val - seg[v*2]);
	}
} begseg, edseg;

struct BIT{
	int bit[100010];
	void update(int i, int val){
		i++;
		for (; i < 100010; i += i&(-i)) bit[i] += val;
	}
	int query(int i){
		i++;
		int ret = 0;
		for (; i > 0; i -= i&(-i)) ret += bit[i];
		return ret;
	}
} bit;


int n, nc, rnk;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nc >> rnk;
	for (int i=0; i<n-1; ++i){
		cin >> arr[i];
	}
	maxseg.build_tree(1, 0, n-2);
	begseg.build_tree(1, 0, n-1);
	edseg.build_tree(1, 0, n-1);
	vector<pair<pair<int,int>, int> > rs;
	for (int qq=0; qq<nc; ++qq){
		int l, r; cin >> l >> r;
		++l; ++r; //l-th to the r-th
		int l2 = begseg.query(1, 0, n-1, l);
		int r2 = edseg.query(1, 0, n-1, r);
		begseg.update(1, 0, n-1, l2+1, r2);
		edseg.update(1, 0, n-1, l2, r2 - 1);
		rs.push_back(make_pair(make_pair(l2, r2), qq+1)); //comes with time 
	}
	sort(rs.begin(), rs.end()); reverse(rs.begin(), rs.end());
	int ans = -1, ansp = -1;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Qans, Qadd;
	Qans.push(make_pair(nc+1, 1e9));
	for (int i=0; i<n; ++i){
		while (!rs.empty() && rs.back().first.first <= i){
			int mval = maxseg.querymax(1, 0, n-2, rs.back().first.first, rs.back().first.second - 1);
			if (mval <= rnk){
				bit.update(rs.back().second, 1);
				Qadd.push(make_pair(rs.back().first.second, rs.back().second));
			}
			else{
				Qans.push(make_pair(rs.back().second, rs.back().first.second));
			}
			rs.pop_back();
		}
		while (!Qadd.empty() && Qadd.top().first < i){
			bit.update(Qadd.top().second, -1);
			Qadd.pop();
		}
		while (!Qans.empty() && Qans.top().second < i) Qans.pop();
		int tmpans = bit.query(Qans.top().first - 1);
		// cout << tmpans << endl;
		if (tmpans > ans){
			ans = tmpans;
			ansp = i;
		}
	}
	cout << ansp;
	return 0;
}