#include <bits/stdc++.h>

using namespace std;

//Can also be done using a segment tree
//O(D*sqrt(N)*B^2) to O(D*log(N)*B^2) for both operations
//currently queries are sqrt(N)*B^2 and updates are sqrt(N)*B
//Bottom up segment Tree is better for this kind of stuff
int B, N, ndays, gsize;
int cost[30010], val[30010], dp[180][51]; //group, group size, cash

void fix(int curg){
	memset(dp[curg], 0, sizeof(dp[curg]));
	for (int j=curg*gsize; j<min((curg + 1)*gsize, N); ++j){
		for (int k=B; k>=cost[j]; --k){
			dp[curg][k] = max(dp[curg][k], dp[curg][k-cost[j]] + val[j]);
		}
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);	
	cin >> B >> N >> ndays;
	for (int i=0; i<N; ++i){
		cin >> cost[i] >> val[i];
	}
	gsize = 300;
	for (int i=0; i<N; i += gsize){
		int curg = i/gsize;
		fix(curg);
	}
	int curbest[51];
	for (int qq=0; qq<ndays; ++qq){
		memset(curbest, 0, sizeof(curbest));
		int a, b, L, R;
		cin >> a >> b >> L >> R; --a; --L; --R;
		cost[a] = b; //fix a's group
		fix(a/gsize);
		if (R - L <= 2*gsize){
			for (int i=L; i<=R; ++i){
				for (int k=B; k>=cost[i]; --k){
					curbest[k] = max(curbest[k], curbest[k-cost[i]] + val[i]);
				}
			}
			cout << curbest[B] << '\n';
			continue;
		}
		int lgroup = L/gsize, rgroup = R/gsize; //can optimize a tiny bit
		for (int i=L; i != (lgroup + 1)*gsize; ++i){
			for (int k=B; k>=cost[i]; --k){
				curbest[k] = max(curbest[k], curbest[k-cost[i]] + val[i]);
			}
		}
		for (int i=rgroup*gsize; i <= R; ++i){
			for (int k=B; k>=cost[i]; --k){
				curbest[k] = max(curbest[k], curbest[k-cost[i]] + val[i]);
			}
		}
		for (int i=lgroup+1; i<rgroup; ++i){
			for (int tot = B; tot >= 0; --tot){
				for (int j = tot; j >= 0; --j){
					curbest[tot] = max(curbest[tot], curbest[j] + dp[i][tot - j]);
				}
			}
		}
		cout << curbest[B] << '\n';
	}


	return 0;
}
