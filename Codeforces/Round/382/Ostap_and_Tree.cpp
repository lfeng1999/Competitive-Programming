#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = int(1e9) + 7;
const int MAX_N = 110, MAX_K = 25;
ll dp[MAX_N][MAX_K*2]; //Node, Depth where the next black node is
//Dp calculates # of possibilities.

ll tmp[MAX_K*2 + 5];
vector<int> graph[MAX_N];
int N, K;

void solve(int v, int p){
	dp[v][0] = dp[v][K+1] = 1;
	for (int u : graph[v]){
		if (u == p) continue;
		solve(u, v);
		for (int i=0; i<MAX_K*2+5; ++i)
			tmp[i] = 0;
		for (int v_val = 0; v_val <= 2*K + 1; v_val++){
			for (int u_val = 0; u_val <= 2*K + 1; u_val++){
				int curr = min(v_val, u_val + 1);

				if (u_val + v_val + 1 > 2*K + 1){
					curr = max(v_val, u_val + 1);
				}
				tmp[curr] = (tmp[curr] + dp[v][v_val]*dp[u][u_val]) % MOD;

			}
		}
		for (int i=1; i<=2*MAX_K + 1; ++i){
			dp[v][i] = tmp[i];
		}
	}
}


int main(){
	// freopen("CF.txt","r",stdin);
	cin >> N >> K;
	for (int i=0; i<N-1; ++i){
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	solve(1, -1);

	ll ans = 0;
	for (int i=0; i<=K; ++i){
		ans = (ans + dp[1][i]) %  MOD;
	}
	cout << ans;

	return 0;	
}