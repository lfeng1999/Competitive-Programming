#include <bits/stdc++.h>

using namespace std;

typedef pair<int,pair<int,int>> pipii;
int n, m, a, b, c, d, g[1010][1010], bestsum[1010][1010];
pair<int,int> idx[1010][1010];
//a, c is widths b, d are heights

int get_sum(int r, int c, int w, int h){
	return g[r][c] - g[r+h][c] - g[r][c+w] + g[r+h][c+w];
}
priority_queue<pipii, vector<pipii>, greater<pipii>> Qs[1010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> m >> n >> a >> b >> c >> d;
	for (int i=0; i<1010; ++i) fill(bestsum[i], bestsum[i] + 1010, 1e9);
	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j){
			cin >> g[i][j];
		}
	}
	for (int i=n-1; i>=0; --i){
		for (int j=m-1; j>=0; --j){
			g[i][j] += g[i+1][j] + g[i][j+1] - g[i+1][j+1];
		}
	}
	for (int i=n-d-1; i>=1; --i){
		priority_queue<pipii, vector<pipii>, greater<pipii>> Q;
		for (int j=m-c-1; j>=1; --j){
			Qs[j].push(make_pair(get_sum(i, j, c, d), make_pair(i, j)));
			while (abs(Qs[j].top().second.first - i) > b - 2 - d){
				Qs[j].pop();
			}
			Q.push(Qs[j].top());
			while (abs(Q.top().second.second - j) > a - 2 - c){
				Q.pop();
			}
			bestsum[i][j] = Q.top().first;
			idx[i][j] = Q.top().second;
		}
	}

	int ans = 0;
	int r1, c1, r2, c2;
	for (int i=0; i<n-b+1; ++i){
		for (int j=0; j<m-a+1; ++j){
			if (get_sum(i, j, a, b) - bestsum[i+1][j+1] > ans){
				ans = get_sum(i, j, a, b) - bestsum[i+1][j+1];
				r1 = i, c1 = j;
				r2 = idx[i+1][j+1].first, c2 = idx[i+1][j+1].second;
			}
		}
	}
	r1++; c1++; r2++; c2++;
	cout << c1 << " " << r1 << '\n';
	cout << c2 << " " << r2 << '\n';


	return 0;
}