#include <bits/stdc++.h>

using namespace std;

int n, m, tele[2000010], src = 0, snk = 2000001;
// map<pair<int,int>, int> comp;
int nxt[2000010], comp[4000010];
bool past[2000010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int qq=0; qq<n; ++qq){
		int v, u; cin >> v >> u;
		tele[v] = u;
		tele[u] = v;
	}
	int nv = 1;
	for (int i=0; i<=snk*2+1; ++i){
		if (i%2 && tele[i/2] != 0){
			++nv;
		}
		comp[i] = nv - 1;
	}
	for (int i=0; i<=snk; ++i){
		if (tele[i] != 0){
			nxt[comp[i*2]] = comp[tele[i]*2 + 1];
			// cout << comp[i*2] << " " << comp[tele[i]*2 + 1] << endl;
		}
	}
	int mainlen = 0;
	int v = 0;
	while (v != nv - 1){
		past[v] = true;
		v = nxt[v];
		mainlen++;
	}
	past[nv-1] = true;
	vector<int> clens;
	for (int i=0; i<nv; ++i){
		if (past[i]) continue;
		v = i;
		int clen = 0;
		while (!past[v]){
			past[v] = true;
			v = nxt[v];
			++clen;
		}
		clens.push_back(clen);
	}
	sort(clens.begin(), clens.end());
	int ans = mainlen;
	while (!clens.empty() && m != 0){
		ans += 2 + clens.back();
		clens.pop_back();
		--m;
	}
	if (m%2 == 0) ans += m*2;
	else ans += m*2 - 1;
	cout << ans;
	return 0;
}