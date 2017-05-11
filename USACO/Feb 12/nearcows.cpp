#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
struct Edge{
	lint v, u;
} es[200010];

vector<lint> graph[100010];
lint n, k, ans[200010][20], val[200010];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;

	for (lint qq=0; qq<n-1; ++qq){
		lint v, u; cin >> v  >> u;
		es[qq*2].v = v, es[qq*2].u = u;
		graph[v].push_back(qq*2);
		es[qq*2+1].v = u, es[qq*2+1].u = v;
		graph[u].push_back(qq*2+1);
	}
	for (lint i=1; i<=n; ++i){
		cin >> val[i];
	}
	for (lint i=0; i<2*n-2; ++i){
		ans[i][0] = val[es[i].u];
	}
	for (lint j=1; j<=k-1; ++j){
		for (lint v=1; v<=n; ++v){
			lint tot = 0;
			for (lint ei : graph[v]){
				tot += ans[ei][j-1];
			}
			for (lint ei : graph[v]){
				ans[ei^1][j] = val[v] + tot - ans[ei][j-1];
			}
		}
	}
	for (lint v=1; v<=n; ++v){
		lint tot = val[v];
		for (lint ei : graph[v]){
			tot += ans[ei][k-1];
		}
		cout << tot << '\n';
	}
	return 0;
}