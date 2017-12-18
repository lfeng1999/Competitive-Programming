#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct State{
	int r, c, t, dir;
};

char grid[1010][1010];
bool past[1010][1010][3][4];
int n, m, sx, sy, ex, ey, mv[4][2] = {{0, -1}, {1,0},{0,1},{-1, 0}};

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=m; ++j){
			cin >> grid[i][j];
			if (grid[i][j] == 'S'){
				sx = i, sy = j;
				grid[i][j] = '.';
			}
			else if (grid[i][j] == 'T'){
				ex = i, ey = j;
				grid[i][j] = '.';
			}
		}
	}
	queue<State> Q;
	for (int i=0; i<4; ++i){
		Q.push({sx, sy, 0, i});
		past[sx][sy][0][i] = true;
	}
	while (!Q.empty()){
		auto cur = Q.front(); Q.pop();
		int r = cur.r, c = cur.c, t = cur.t, dir = cur.dir;
		if (r == ex && c == ey){
			cout << "YES";
			return 0;
		}
		for (int i=0; i<4; ++i){
			int nr = r + mv[i][0], nc = c + mv[i][1], nt = t + (dir == i?0:1), ndir = i;
			if (nr < 1 || nr > n || nc < 1 || nc > m || nt > 2 || grid[nr][nc] == '*' || past[nr][nc][t][ndir]) continue;
			Q.push({nr, nc, nt, ndir});
			past[nr][nc][nt][ndir] = true;
		}
	}
	cout << "NO";


	return 0;
}