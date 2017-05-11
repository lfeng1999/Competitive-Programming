#include <bits/stdc++.h>

using namespace std;

int n, k;
int bm[100010][9], fm[100010][9], ncows[100010][8];
vector<pair<int,int>> cows;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("fairphoto.in","r",stdin);
	freopen("fairphoto.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=0; i<n; ++i){
		int x, b; cin >> x >> b; b--;
		cows.push_back(make_pair(x, b));
	}
	sort(cows.begin(), cows.end());
	for (int i=1; i<=8; ++i)
		bm[0][i] = (1 << cows[0].second);
	ncows[0][cows[0].second]++;
	for (int i=1; i<n; ++i){
		for (int j=0; j<8; ++j) ncows[i][j] = ncows[i-1][j];
		ncows[i][cows[i].second]++;
		for (int j=1; j<=8; ++j){
			int nxt = (bm[i-1][j] | (1 << cows[i].second));
			if (__builtin_popcount(nxt) <= j){
				bm[i][j] = nxt;
			}
			else{
				bm[i][j] = (bm[i-1][j-1] | (1 << cows[i].second));
			}
		}
	}
	for (int i=1; i<=8; ++i) fm[n-1][i] = (1 << cows[n-1].second);
	for (int i=n-2; i>=0; --i){
		for (int j=1; j<=8; ++j){
			int nxt = (fm[i+1][j] | (1 << cows[i].second));
			if (__builtin_popcount(nxt) <= j){
				fm[i][j] = nxt;
			}
			else{
				fm[i][j] = (fm[i+1][j-1] | (1 << cows[i].second));
			}
		}
	}
	int best = -1e9;
	for (int l=k; l<=8; ++l){
		vector<int> cur(9, 0);
		map<vector<int>, int> M;
		for (int i=0; i<n; ++i){
			if (__builtin_popcount(bm[i][l]) < l) continue;
			cur[0] = (bm[i][l]); //insert mask
			bitset<8> b = bm[i][l];
			int beg = -1;
			for (int j=0; j<8; ++j){
				if (b.test(j)){
					if (beg == -1) beg = j;
					cur[j+1] = (ncows[i][j] - ncows[i][beg]);
				}
				else{
					cur[j+1] = (ncows[i][j]);
				}
			}
			M[cur] = cows[i].first;
		}
		for (int i=n-1; i>=0; --i){
			if (__builtin_popcount(fm[i][l]) < l) continue;
			cur[0] = (fm[i][l]);
			bitset<8> b = fm[i][l];
			int beg = -1;
			if (i > 0)
			for (int j=0; j<8; ++j){
				if (b.test(j)){
					if (beg == -1) beg = j;
					cur[j+1] = (ncows[i-1][j] - ncows[i-1][beg]);
				}
				else{
					cur[j+1] = (ncows[i-1][j]);
				}
			}
			else{
				for (int j=0; j<8; ++j) cur[j+1] = (0);
			}
			auto it = M.find(cur);
			if (it != M.end()){
				// cout << cows[i].first << " " << it->second << endl; 
				best = max(best, it->second - cows[i].first);
			}
		}
	}
	if (best >= 0) cout << best;
	else cout << -1;
	return 0;
}