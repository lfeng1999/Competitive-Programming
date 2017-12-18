#include <bits/stdc++.h>

using namespace std;

bool blocked[101][101][101][101], iscow[110][110], past[110][110];
int mv[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
int N, K, R, cow_cnt = 0;

void dfs(int r, int c){
	if (iscow[r][c])
		cow_cnt++;

	past[r][c] = true;
	for (int i=0; i<4; ++i){
		int nr = r + mv[i][0], nc = c + mv[i][1];
		if (1 <= nr && nr <= N && 1 <= nc && nc <= N && !blocked[r][c][nr][nc] && !past[nr][nc]){
			dfs(nr, nc);
		}
	}
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> K >> R;

	for (int i=1; i<=R; ++i){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		blocked[a][b][c][d] = blocked[c][d][a][b] = true;
	}
	for (int i=1; i<=K; ++i){
		int r, c;
		cin >> r >> c;
		iscow[r][c] = true;
	}
	int ans = K*(K-1)/2;
	for (int i=1; i<=N; ++i){
		for (int j=1; j<=N; ++j){
			if (past[i][j]) continue;
			dfs(i, j);
			ans -= cow_cnt*(cow_cnt-1)/2;
			cow_cnt = 0;
		}
	}
	cout << ans;


	return 0;
}