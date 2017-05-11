#include <bits/stdc++.h>

using namespace std;

inline int two(int n){return 1 << n;}
inline bool test(int n, int b){return (n >> b) & 1;}
int grid[16][16], n, k;

bool valid(int msize, int msk, int left){
	int cnt = 0, r[16], p = 0; memset(r, 0, sizeof(r));

	for (int i=0; i<n; ++i){
		bool isover = false;
		p = 0;
		for (int j=0; j<n; ++j){
			r[p] += grid[i][j];
			if (r[p] > msize) isover = true;
			if (test(msk, j)) p++;
		}
		if (isover){
			cnt++;
			isover = false;
			p=0;
			memset(r, 0, sizeof(r));
			for (int j=0; j<n; ++j){
				r[p] += grid[i][j];
				if (r[p] > msize) return false;
				if (test(msk, j)) p++;
			}
		}
	}

	return cnt <= left;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("partition.in","r",stdin);
	freopen("partition.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			cin >> grid[i][j];
		}
	}
	int ans = 1e9;
	for (int msk=0; msk<two(n-1); ++msk){
		int nv = __builtin_popcount(msk);
		if (nv > k) continue;
		int L = 0, R = 225000;
		while (L < R){
			int mid = (L+R)/2;
			if (valid(mid, msk, k - nv)){
				R = mid;
			}
			else{
				L = mid+1;
			}
		}
		ans = min(ans, L);
	}
	cout << ans;
	return 0;
}