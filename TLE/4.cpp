#include <bits/stdc++.h>

using namespace std;

bool valid[360][360][360];
int best_cnt[360], cur_best, R, C, M;

void remove_square(int r, int c, int len){
	if (r < 1 || c < 1 || r + len > R + 1 || c + len > C + 1) return;
	if (!valid[r][c][len]) return;

	valid[r][c][len] = false;
	best_cnt[len]--;

	remove_square(r-1, c, len+1);
	remove_square(r-1, c-1, len+1);
	remove_square(r, c-1, len+1);
	remove_square(r, c, len+1);
}

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	memset(valid, true, sizeof(valid));

	cin >> R >> C >> M;

	for (int i=0; i<min(R, C); ++i){
		best_cnt[i+1] = (R - i)*(C - i);
	}
	
	cur_best = min(R, C);

	for (int qq=0; qq<M; ++qq){
		int r, c;
		cin >> r >> c;
		remove_square(r, c, 1);

		while (cur_best > 0 && best_cnt[cur_best] == 0){
			cur_best--;
		}

		cout << cur_best << '\n';

	}

	return 0;
}