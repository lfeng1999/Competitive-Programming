#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct Update{
	int x, y, t, typ;
	bool operator < (const Update &a) const {
		return x < a.x;
	}
};
struct Query{
	int x, y1, y2, t;
	bool operator < (const Query &a) const{
		return x < a.x;
	}
};

struct Node{
	Node *lef = nullptr, *rig = nullptr;
	int val = 0;

	void update(int L, int R, int p, int uval){
		if (L == R){
			val += uval;
			return;
		}
		int mid = (L+R)/2;
		if (p <= mid){
			if (!lef) lef = new Node();
			lef->update(L, mid, p, uval);
		}
		else{
			if (!rig) rig = new Node();
			rig->update(mid+1, R, p, uval);
		}
		val = 0;
		if (lef) val += lef->val;
		if (rig) val += rig->val;
	}
	int query(int L, int R, int QL, int QR){
		int ret = 0;
		if (QR < L || R < QL) return 0;
		if (QL <= L && R <= QR) return val;
		int mid = (L+R)/2;
		return (lef?lef->query(L, mid, QL, QR):0) + (rig?rig->query(mid+1, R, QL, QR):0);
	}

} bit[100010];

int n, T, nxx = 0, nyy = 0;
vector<Update> us;
vector<Query> qs;

void update(int i, int t, int val){
	for (; i <= nyy; i += i&(-i))
		bit[i].update(1, n, t, val);
}

int query(int i, int t1, int t2){
	int ret = 0;
	for (; i > 0; i -= i&(-i))
		ret += bit[i].query(1, n, t1, t2);
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("mowing.in","r",stdin);
	freopen("mowing.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> T;
	int x, y; cin >> x >> y;
	map<int,int> compx, compy;
	for (int i=1; i<=n-1; ++i){
		int x2, y2; cin >> x2 >> y2;
		if (x == x2){
			qs.push_back({x, min(y, y2), max(y, y2), i});
			compx[x] = compy[y] = compy[y2] = 0;
		}
		else if (y == y2){
			us.push_back({min(x, x2)+1, y, i, 1});
			compx[max(x, x2)] = compx[min(x, x2)+1] = compy[y] = 0;
			us.push_back({max(x, x2), y, i, -1});
		}
		x = x2, y = y2;
	}
	for (auto &it : compx){
		it.second = ++nxx;
	}
	for (auto &it : compy){
		it.second = ++nyy;
	}
	sort(qs.begin(), qs.end());
	sort(us.begin(), us.end());
	for (auto &it : qs){
		it.x = compx[it.x];
		it.y1 = compy[it.y1];
		it.y2 = compy[it.y2];
	}
	for (auto &it : us){
		it.x = compx[it.x];
		it.y = compy[it.y];
	}
	int R = 0;
	lint ans = 0;
	for (auto &it : qs){
		while (R < us.size() && it.x >= us[R].x){
			update(us[R].y, us[R].t, us[R].typ);
			R++;
		}
		lint recent = query(it.y2-1, it.t - T + 1, it.t + T - 1) - query(it.y1, it.t - T + 1, it.t + T - 1);
		lint total = query(it.y2-1, 1, n) - query(it.y1, 1, n);
		ans += total - recent;
	}
	cout << ans;

	return 0;
}