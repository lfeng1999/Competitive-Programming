#include <bits/stdc++.h>

using namespace std;

inline int two(int x){return 1 << x;}
#define DEBUG(x) cout << '>' << #x << ':' << x << endl

int g[16][16], inum[51][51];
char grid[51][51];
int R, C, n, dp[16][40010], mv[4][2] = {{1, 0}, {0, 1}, {-1,0}, {0,-1}};
bool past[51][51], ipast[16];
bool inq[16][40010];

bool isout(int r, int c){return r < 1 || r > R || c < 1 || c > C;}

void flood(int r, int c){
	if (isout(r, c) || grid[r][c] != 'X' || past[r][c]) return;
	inum[r][c] = n;
	past[r][c] = true;
	for (int i=0; i<4; ++i) flood(r + mv[i][0], c + mv[i][1]);
}
void flood2(int id){
	memset(past, false, sizeof(past));
	bool ipast[16]; memset(ipast, false, sizeof(ipast));
	ipast[id] = true;
	priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int,pair<int,int>>>> Q;
	int fker = 0;
	for (int i=1; i<=R; ++i){
		for (int j=1; j<=C; ++j){
			if (grid[i][j] == 'X' && inum[i][j] == id){
				Q.push(make_pair(0, make_pair(i, j)));
				past[i][j] = true;
			}
		}
	}
	while (!Q.empty()){
		int r = Q.top().second.first, c = Q.top().second.second, d = Q.top().first;
		Q.pop();
		if (grid[r][c] == 'X'){
			if (!ipast[inum[r][c]]){
				g[id][inum[r][c]] = d;
				ipast[inum[r][c]] = true;
				for (int i=1; i<=R; ++i){
					for (int j=1; j<=C; ++j){
						if (grid[i][j] == 'X' && inum[i][j] == inum[r][c] && !past[i][j]){
							past[i][j] = true;
							Q.push(make_pair(d, make_pair(i, j)));
						}
					}
				}
			}
		}
		for (int i=0; i<4; ++i){
			int nr = r + mv[i][0], nc = c + mv[i][1], nd = d + (grid[nr][nc] == 'S'?1:0);
			if (grid[nr][nc] == '.' || isout(nr, nc) || past[nr][nc]) continue;
			past[nr][nc] = true;
			Q.push(make_pair(nd, make_pair(nr, nc)));
		}
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	memset(inum, -1, sizeof(inum));
	for (int i=0; i<16; ++i)
		fill(dp[i], dp[i]+40010, 1e9);
	cin >> R >> C;
	for (int i=1; i<=R; ++i){
		for (int j=1; j<=C; ++j){
			cin >> grid[i][j];
		}
	}
	n = 0;
	for (int i=1; i<=R; ++i){
		for (int j=1; j<=C; ++j){
			if (!past[i][j] && grid[i][j] == 'X'){
				flood(i, j);
				n++;
			}
		}
	}
	for (int i=0; i<16; ++i) fill(g[i], g[i] + 16, 1e9);
	for (int i=0; i<n; ++i){
		flood2(i);
	}
	queue<pair<int,int>> Q;
	for (int i=0; i<n; ++i){
		dp[i][two(i)] = 0;
		inq[i][two(i)] = true;
		Q.push(make_pair(i, two(i)));
	}
	while (!Q.empty()){
		int cur = Q.front().first, msk = Q.front().second; Q.pop();
		bitset<20> b = msk;
		for (int i=0; i<n; ++i){
			if (!b.test(i)){
				int nmsk = (msk | two(i));
				dp[i][nmsk] = min(dp[i][nmsk], dp[cur][msk] + g[cur][i]);
				if (!inq[i][nmsk]){
					Q.push(make_pair(i, nmsk));
					inq[i][nmsk] = true;
				}
			}
		}
	}
	int ans = 1e9;
	for (int i=0; i<n; ++i){
		ans = min(ans, dp[i][(1 << n) - 1]);
	}
	cout << ans;
	return 0;
}