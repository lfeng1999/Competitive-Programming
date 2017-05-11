#include <bits/stdc++.h>

using namespace std;

int n, k, dp[100010][21];
vector<int> graph[100010];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=0; i<n-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u); graph[u].push_back(v);
	}
	for (int i=1; i<=n; ++i){
		cin >> dp[i][0];
	}
	for (int i=1; i<=k; ++i){
		for (int v=1; v<=n; ++v){
			if (i >= 2){
				dp[v][i] -= (graph[v].size()-1)*dp[v][i-2]; //the overlap edges
			}
			else{
				dp[v][i] = dp[v][i-1];
			}
			for (int u : graph[v]){
				dp[v][i] += dp[u][i-1];
			}
			if (i == k){
				cout << dp[v][i] << '\n';
			}
		}
	}
	return 0;
}