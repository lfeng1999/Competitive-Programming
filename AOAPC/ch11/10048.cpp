#include <bits/stdc++.h>

using namespace std;

int dp[110][110], C, S, Q;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int t = 0;
	while (cin >> C >> S >> Q && (C || S || Q)){
		if (t)
			printf("\n");
		for (int i=0; i<110; ++i)
			fill(dp[i], dp[i] + 110, (int)1e9);
		while (S--){
			int v, u, d; cin >> v >> u >> d;
			dp[v][u] = dp[u][v] = d;
		}

		for (int j=1; j<=C; ++j)
			for (int i=1; i<=C; ++i)
				for (int k=1; k<=C; ++k)
					dp[i][k] = min(dp[i][k], max(dp[i][j], dp[j][k]));

		printf("Case #%d\n", ++t);
		while (Q--){
			int v, u; cin >> v >> u;
			if (dp[v][u] == (int)1e9){
				printf("no path\n");
			}
			else{
				printf("%d\n", dp[v][u]);
			}
		}
	}

	return 0;
}