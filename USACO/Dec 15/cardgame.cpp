#include <bits/stdc++.h>

using namespace std;

int a1[50010], a2[50010], n, mv[50010];
set<int> bes, els;
bool used[100010];
map<int,int> M;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("cardgame.in","r",stdin);
	freopen("cardgame.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		int x; cin >> x;
		mv[i+1] = x;
		used[x] = true;
	}
	for (int i=1; i<=2*n; ++i){
		if (!used[i]) bes.insert(i);
	}
	for (int i=1; i<=n; ++i){
		auto it = bes.upper_bound(mv[i]);
		a1[i] = a1[i-1];
		if (it != bes.end()){
			bes.erase(it);
			a1[i]++;
		}
	}
	bes.clear();
	for (int i=1; i<=2*n; ++i){
		if (!used[i]) bes.insert(i);
	}
	for (int i=n; i>=1; --i){
		auto it = bes.upper_bound(mv[i]);
		a2[i] = a2[i+1];
		if (it != bes.begin()){
			bes.erase(--it);
			a2[i]++;
		}
	}

	int ans = 0;
	for (int i=0; i<=n; ++i){
		ans = max(ans, a1[i] + a2[i+1]);
	}

	cout << ans;
	return 0;
}