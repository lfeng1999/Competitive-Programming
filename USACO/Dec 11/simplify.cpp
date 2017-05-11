#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef pair<int, pair<int,int>> pipii;
const lint MOD = 1000000007;
int n, m, root[40010];

int find(int v){
	if (v == root[v]) return v;
	return root[v] = find(root[v]);
}

void merge(int v, int u){
	v = find(v); u = find(u);
	if (v == u) return;
	root[v] = u;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("simplify.in","r",stdin);
	freopen("simplify.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	priority_queue<pipii, vector<pipii>, greater<pipii>> Q, KQ;
	for (lint qq=0; qq<m; ++qq){
		lint v, u, d; cin >> v >> u >> d;
		Q.push(make_pair(d, make_pair(v, u)));
		KQ.push(make_pair(d, make_pair(v, u)));
	}
	for (lint i=1; i<=n; ++i){
		root[i] = i;
	}
	lint mst = 0;
	while (!KQ.empty()){
		lint d = KQ.top().first, v = KQ.top().second.first, u = KQ.top().second.second; KQ.pop();
		v = find(v); u = find(u);
		if (v == u) continue;
		mst += d; merge(v, u);
	}
	for (lint i=1; i<=n; ++i){
		root[i] = i;
	}
	lint nmst = 1;
	while (!Q.empty()){
		lint d = Q.top().first;
		map<pair<lint,lint>, lint> cnt;
		map<lint,lint> nodecnt;
		while (!Q.empty() && Q.top().first == d){
			lint v = Q.top().second.first, u = Q.top().second.second; Q.pop();
			v = find(v); u = find(u);
			if (v == u) continue;
			if (v > u) swap(v, u);
			cnt[make_pair(v, u)]++;
			nodecnt[v]++; nodecnt[u]++;
		}
		for (auto &it : cnt){
			merge(it.first.first, it.first.second);
			nmst *= it.second;
			nmst %= MOD;
		}
		if (nodecnt.size() == 3 && cnt.size() == 3){
			nmst *= 3;
			nmst %= MOD;
		}
	}
	cout << mst << " " << nmst << endl;

	return 0;
}