#include <bits/stdc++.h>

using namespace std;

struct State{
	int r = -1, c = -1, val = -1;
	bool operator < (const State &a){
		return val < a.val;
	}
};

int n, sr, sc, g[1510][1510];
State brow[1510][4], bcol[1510][4];
State makeState(int r, int c, int val){
	State x; x.r = r, x.c =c, x.val = val;
	return x;
}
vector<pair<int,pair<int,int>>> ps;


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	cin >> sr >> sc;
	brow[sr][0] = makeState(sr, sc, 1);
	bcol[sc][0] = makeState(sr, sc, 1);
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=n; ++j){
			cin >> g[i][j];
		}
	}
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=n; ++j){
			if (g[i][j] > g[sr][sc]){
				ps.push_back(make_pair(g[i][j], make_pair(i, j)));
			}
		}
	}
	sort(ps.begin(), ps.end());
	int ans = 1;
	for (int i=0; i<ps.size(); ++i){
		int j = i;
		while (j+1 < ps.size() && ps[j+1].first == ps[i].first) ++j;


		for (int k=i; k<=j; ++k){
			int r = ps[k].second.first, c = ps[k].second.second;
			int bestval = 0;
			for (int l=0; l<4; ++l){
				if (brow[r-1][l].r == -1) break;
				if (abs(brow[r-1][l].c - c) <= 1) continue;
				bestval = max(bestval, brow[r-1][l].val + 1);
				break;
			}
			for (int l=0; l<4; ++l){
				if (brow[r+1][l].r == -1) break;
				if (abs(brow[r+1][l].c - c) <= 1) continue;
				bestval = max(bestval, brow[r+1][l].val + 1);
				break;
			}


			for (int l=0; l<4; ++l){
				if (bcol[c-1][l].c == -1) break;
				if (abs(bcol[c-1][l].r - r) <= 1) continue;
				bestval = max(bestval, bcol[c-1][l].val + 1);
				break;
			}
			for (int l=0; l<4; ++l){
				if (bcol[c+1][l].c == -1) break;
				if (abs(bcol[c+1][l].r - r) <= 1) continue;
				bestval = max(bestval, bcol[c+1][l].val + 1);
				break;
			}
			if (bestval == 0){
				g[r][c] = -1;
				continue;
			}
			g[r][c] = bestval;
			ans = max(ans, bestval);
		}
		for (int k=i; k<=j; ++k){
			int r = ps[k].second.first, c = ps[k].second.second;
			if (g[r][c] == -1) continue;
			State cur = makeState(r, c, g[r][c]);
			brow[cur.r][3] = cur;
			bcol[cur.c][3] = cur;
			for (int l=2; l>=0; --l){
				if (brow[cur.r][l] < brow[cur.r][l+1])
					swap(brow[cur.r][l], brow[cur.r][l+1]);
			}
			for (int l=2; l>=0; --l){
				if (bcol[cur.c][l] < bcol[cur.c][l+1])
					swap(bcol[cur.c][l], bcol[cur.c][l+1]);
			}
		}



		i = j;
	}
	cout << ans;



	return 0;
}