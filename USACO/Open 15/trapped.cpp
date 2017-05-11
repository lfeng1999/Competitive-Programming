#include <bits/stdc++.h>

using namespace std;

int rootl[100010], rootr[100010], lsize[100010], rsize[100010], n;
int wall[100010], failed[100010], bsize[100010];

int find(int *root, int x){
	if (x == root[x]) return x;
	return root[x] = find(root, root[x]);
}

void merge(int v, int u){
	v = find(rootl, v), u = find(rootl, u);
	if (v > u) swap(v, u);
	lsize[v] += lsize[u];
	rootl[u] = v;

	v = find(rootr, v), u = find(rootr, u);
	if (v < u) swap(v, u);
	rootr[u] = v;
	rsize[v] += rsize[u];
}


int main(){
	// freopen("test.txt","r",stdin);
	freopen("trapped.in","r",stdin);
	freopen("trapped.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	vector<pair<int,int>> hay;
	for (int i=0; i<n; ++i){
		int sz, p; cin >> sz >> p;
		hay.push_back(make_pair(p, sz));
	}
	sort(hay.begin(), hay.end());
	lsize[0] = rsize[0] = 1e6; //MAKE 1e17 FOR LONG LONG
	for (int i=0; i < n; ++i){
		wall[i] = hay[i].second;
		rootl[i] = rootr[i] = i; //setup dsu
		if (i != 0){
			lsize[i] = rsize[i] = bsize[i] = hay[i].first - hay[i-1].first;
		}
	}
	lsize[n] = rsize[n] = 1e6; //MAKE 1e17 FOR LONG LONG
	set<pair<int,int>> blocks; //size and left most position
	for (int i=1; i<n; ++i){
		blocks.insert(make_pair(lsize[i], i));
	}

	while (!blocks.empty()){
		auto it = *blocks.begin(); blocks.erase(blocks.begin());
		int sz = it.first, L = it.second, R = find(rootr, L);
		if (L == 0 || R == n){
			continue;
		}
		if (wall[L-1] >= sz && sz <= wall[R]){ //can't break side walls
			failed[L]++; failed[R+1]--; //failed block
			continue;
		}
		int nL = L, nR = R;
		if (wall[L-1] < sz){
			nL = find(rootl, L-1);
			blocks.erase(make_pair(lsize[nL], nL));
			merge(L-1, L);
		}
		if (sz > wall[R]){
			nR = find(rootr, R+1);
			blocks.erase(make_pair(rsize[nR], R+1));
			merge(R, R+1);
		}
		L = find(rootl, L);
		sz = lsize[L];
		blocks.insert(make_pair(sz, L));
	}
	int ans = 0;
	for (int i=1; i<=n; ++i){
		failed[i] += failed[i-1];
		if (failed[i] != 0){
			ans += bsize[i];
		}
	}
	cout << ans;

	return 0;
}