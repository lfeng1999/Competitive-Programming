#include <bits/stdc++.h>

using namespace std;

int par[262150][64], n;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("262144.in","r",stdin);
	freopen("262144.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	memset(par, -1, sizeof(par));
	int best = 0;
	for (int i=1; i<=n; ++i){
		int x; cin >> x;
		par[i][x] = i-1;
		for (int j=1; j<63; ++j){
			if (par[i][j] >= 0){
				par[i][j+1] = par[par[i][j]][j];
				best = max(best, j);
			}
		}
	}
	cout << best;
	return 0;
}