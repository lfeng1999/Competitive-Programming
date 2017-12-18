#include <bits/stdc++.h>

using namespace std;

int n, X[510], Y[510];
int dist[510][510];
int furthest[510];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> X[i] >> Y[i];
	}
	for (int i=0; i<n; ++i){
		for (int j=i+1; j<n; ++j){
			dist[i][j] = dist[j][i] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
		}
	}
	int finans = 2e9;
	for (int i=0; i<n; ++i){
		memset(furthest, 0, sizeof(furthest));
		vector<pair<int,int>> ds;
		for (int j=0; j<n; ++j){
			ds.push_back({dist[i][j], j});
		}
		sort(ds.begin(), ds.end(), greater<pair<int,int>>());
		for (int j=0; j<n; ++j){
			if (i == j) continue;
			int nfar = 0;
			int ans = ds[0].first + ds[1].first;
			int top2[3] = {0, 0, 0};
			for (int l = 0; l < ds.size() - 1; ++l){
				nfar = max(nfar, dist[j][ds[l].second]);
				top2[2] = dist[j][ds[l].second];
				for (int k=1; k>=0; --k){
					if (top2[k+1] > top2[k]) swap(top2[k], top2[k+1]);
				}

				if (top2[0] + top2[1] > nfar + ds[l+1].first + dist[i][j]) break;
				
				ans = min(ans, nfar + ds[l+1].first + dist[i][j]);
			}
			finans = min(finans, ans);
		}
	}
	cout << finans;
	return 0;
}