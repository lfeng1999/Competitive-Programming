#include <bits/stdc++.h>

using namespace std;

int open_when[355][355][355], grid[355][355], ans[355], square_tm[355];
int R, C, M;

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<355; ++i){
		square_tm[i] = 1e9;
	}

	cin >> R >> C >> M;

	for (int i=0; i<M; ++i){
		int r, c; cin >> r >> c;
		grid[r][c] = M - i;
	}
	for (int r=1; r<=R; ++r){
		for (int c=1; c<=C; ++c){
			open_when[r][c][1] = grid[r][c];
			square_tm[1] = min(square_tm[1], grid[r][c]);
		}
	}	
	int max_len = min(R, C);
	for (int len = 2; len <= max_len; ++len){
		square_tm[len] = 1e9;
		for (int r = len; r <= R; ++r){
			for (int c = len; c <= C; ++c){
				open_when[r][c][len] = max(max(open_when[r][c][len-1], open_when[r-1][c-1][len-1]), max(open_when[r-1][c][len-1], open_when[r][c-1][len-1]));
				square_tm[len] = min(open_when[r][c][len], square_tm[len]);
			}
		}
	}
	int cur_square = 0;
	vector<int> answers;
	for (int i=0; i<M; ++i){

		while (square_tm[cur_square+1] <= i){
			cur_square++;
		}
		answers.push_back(cur_square);
	}

	for (int i=M-1; i>=0; --i){
		cout << answers[i] << '\n';
	}



	return 0;
}