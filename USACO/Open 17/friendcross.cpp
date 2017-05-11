#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int N, K, a[100010], b[100010];
pair<int,int> c[100010];

struct BIT{
	int tree[100010], tot = 0;
	void add(int i, int val){
		tot += val;
		for (; i <= N; i += i&(-i))
			tree[i] += val;
	}
	int f(int i){
		int ret = 0;
		for (; i > 0; i -= i&(-i))
			ret += tree[i];
		return ret;
	}
	int query(int st, int ed){
		if (st > ed) return 0;
		return f(ed) - f(st-1);
	}
} bit;

lint merge(int L, int R){
	if (L == R) return 0;

	int mid = (L+R)/2;
	lint ret = merge(L, mid) + merge(mid+1, R);

	vector<pair<int,int>> l, r;

	for (int i=L; i<=mid; ++i){
		l.push_back(c[i]);
	}
	for (int i=mid+1; i<=R; ++i){
		r.push_back(c[i]);
	}
	sort(l.begin(), l.end()); sort(r.begin(), r.end());
	//now find # of inversions that satisfy |a-b| > K
	int nr = 0;
	for (auto &it : l){
		while (nr < r.size() && r[nr].first < it.first){
			bit.add(r[nr++].second, 1);
		}
		ret += bit.query(1, it.second - K - 1) + bit.query(it.second + K + 1, N); //Use 2 chains
		// ret += bit.tot - bit.query(it.second - K, min(it.second + K, N)); //NOT THIS. you need to do min() for it to work... :/ fuck my life y man... 
		//it's cuz bit
	}
	for (int i=0; i<nr; ++i){
		bit.add(r[i].second, -1);
	}
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("friendcross.in","r",stdin);
	freopen("friendcross.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		a[x] = i;
	}
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		b[x] = i;
	}
	for (int i=1; i<=N; ++i){
		c[a[i]] = make_pair(b[i], i);
	}
	cout << merge(1, N);
	return 0;
}