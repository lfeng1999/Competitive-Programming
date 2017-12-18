#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9;
int N, M, dp[10010], disc[10010], tm = 1;
vector<int> graph[10010], graph2[10010];
bool revpast[10010], past[10010], moredig = false, is_cycle = false, in_path[10010];
vector<int> stk;

void revdfs(int v){
	revpast[v] = true;
	for (int u : graph2[v]){
		if (!revpast[u])
			revdfs(u);
	}
}

void modulo(int &x){
	if (x >= MOD){
		moredig = true;
	}
	x %= MOD;
}

void dfs(int v){
	past[v] = true;
	in_path[v] = true;
	for (int u : graph[v]){
		if (!revpast[u]) continue;
		if (past[u]){
			if (in_path[u])
				is_cycle = true;
			continue;
		}
		dfs(u);
	}
	in_path[v] = false;
	stk.push_back(v);
}



int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i=0; i<M; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u);
		graph2[u].push_back(v);
	}
	revdfs(2);

	fill(dp, dp + 10010, -1);
	dfs(1);
	if (is_cycle){
		printf("inf");
		return 0;
	}

	dp[stk[0]] = 1;
	for (int i=1; i<stk.size(); ++i){
		int v = stk[i];
		dp[v] = 0;
		for (int u : graph[v]){
			if (!revpast[u]) continue;
			dp[v] += dp[u];
			modulo(dp[v]);
		}
	}
	if (moredig){
		printf("%09d", dp[1]);
	}
	else{
		printf("%d", dp[1]);
	}

	return 0;
}