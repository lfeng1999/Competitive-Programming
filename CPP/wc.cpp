#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

char grid[4][110];
int sdist[4][110], mv[4][2] = {{1, 0}, {-1,0}, {0,1}, {0,-1}};
bool past[4][110];

int solvepls(int C){
	for (int i=0; i<4; ++i){
		fill(sdist[i], sdist[i] + C+1, 0);
	}
	memset(past, false, sizeof(past));
	int sr, sc, er = 0, ec = 0;
	for (int i=0; i<4; ++i){
		for (int j=0; j<=C; ++j){
			if (grid[i][j] == 'S'){
				sr = i, sc = j;
			}
			else if (grid[i][j] == 'E'){
				er = i, ec = j;
			}
			else if (grid[i][j] == '#'){
				past[i][j] = true;
			}
		}
	}
	queue<pair<int,int>> Q;
	Q.push(make_pair(sr, sc));
	while (!Q.empty()){
		int r = Q.front().first, c = Q.front().second;
		Q.pop();
		for (int i=0; i<4; ++i){
			int nr = r + mv[i][0], nc = c + mv[i][1];
			if (nr > 4 || nr < 0 || nc > C || nc < 0){
				continue;
			}
			if (past[nr][nc]) continue;
			sdist[nr][nc] = sdist[r][c] + 1;
			past[nr][nc] = true;
			Q.push(make_pair(nr, nc));
		}
	}
	for (int i=0; i<4; ++i){
		for (int j=1; j<=C; ++j){
			cout << setw(3) << sdist[i][j];
		}
		cout << endl;
	}
	return sdist[er][ec];
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	int N;
	cin >> N;
	for (int i=0; i<N; ++i){
		int C;
		cin >> C;

		for (int i=0; i<4; ++i){
			for (int j=1; j<=C; ++j){
				grid[i][j] = '.';
			}
		}

		int r1 = 1, r2 = 3;

		for (int c = C; c >= 1; --c){
			grid[r1][c] = 'x';
			grid[r2][c] = 'x';
			if (r2 == 3){
				if (grid[1][c+1] == 'x' && grid[0][c+1] == 'x' && r1 == 0){
					r2--;
					grid[2][c] = 'x';
				}
			}
			else if (r2 == 2){
				if (grid[3][c+1] != 'x'){
					r2++;
					grid[3][c] = 'x';
				}
			}
			if (r1 == 0){
				if (grid[2][c+1] == 'x' && grid[3][c+1] == 'x' && r2 == 3){
					r1++;
					grid[1][c] = 'x';
				}
			}
			else if (r1 == 1){
				if (grid[0][c+1] != 'x'){
					r1--; //now 0
					grid[0][c] = 'x';
				}
			}

		}
		for (int i=0;i<4; ++i){
			grid[i][1] = 'x';
		}
		if (C == 1){
			for (int i=0; i<4; ++i){
				grid[i][1] = 'x';
			}
			grid[0][C] = 'E';
			grid[3][C] = 'S';
		}
		else if (C == 2){
			for (int i=0; i<4; ++i){
				grid[i][1] = grid[i][2] = 'x';
			}
			grid[1][2] = grid[2][2] = '.';
			grid[0][C] = 'E';
			grid[3][C] = 'S';
		}
		else{
			grid[1][C] = 'E';
			grid[3][C] = 'S';
		}

		for (int i=0; i<4; ++i){
			for (int j=1; j<=C; ++j){
				if (grid[i][j] == '.'){
					grid[i][j] = '#';
				}
				else if (grid[i][j] == 'x'){
					grid[i][j] = '.';
				}
			}
		}
		cout << solvepls(C) << '\n';
		for (int i=0; i<4; ++i){
			for (int j=1; j<=C; ++j){
				cout << grid[i][j];
			}
			cout << '\n';
		}
	}

	return 0;
}