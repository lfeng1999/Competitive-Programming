#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct BIT{
	int bit[2110][2110];
	int query(int x, int y){
		int ret = 0;
		++x; ++y;
		for (int i=x; i > 0; i -= i&(-i)){
			for (int j=y; j > 0; j -= j&(-j)){
				ret += bit[i][j];
			}
		}
		return ret;
	}
	void update(int x, int y, int val){
		++x; ++y;
		for (int i=x; i<2110; i += i&(-i)){
			for (int j=y; j<2110; j += j&(-j)){
				bit[i][j] += val;
			}
		}
	}
} bit[2];

int nr, nc;

int get_Y(int i, int j){
	return 1000 + j - i;
}	

int get_X(int i, int j){
	return i + j; 
}

char grid[1010][1010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nr >> nc;

	for (int i=nr; i>=1; --i){
		for (int j=1; j<=nc; ++j){
			cin >> grid[j][i];
			if (grid[j][i] != '.'){
				bit[grid[j][i] == 'S'].update(get_X(j, i), get_Y(j, i), 1);
			}
		}
	}
	ll ans[2] = {0, 0};
	for (int i=1; i<=nc; ++i){
		for (int j=1; j<=nr; ++j){
			if (grid[i][j] == '.') continue;
			int typ = (grid[i][j] == 'S');
			int cx = get_X(i, j), cy = get_Y(i, j);
			ans[typ] += (ll)bit[typ].query(cx, cy-1)*j;
			ans[typ] -= (ll)(bit[typ].query(2099, 2099) - bit[typ].query(2099, cy) - bit[typ].query(cx-1, 2099) + bit[typ].query(cx-1, cy))*j;

			ans[typ] += (ll)(bit[typ].query(cx-1, 2099) - bit[typ].query(cx-1, cy-1))*i;
			ans[typ] -= (ll)(bit[typ].query(2099, cy) - bit[typ].query(cx, cy))*i;
		}
	}
	cout << ans[0] << " " << ans[1];


	return 0;
}