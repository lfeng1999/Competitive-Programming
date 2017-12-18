#include <bits/stdc++.h>

using namespace std;

int N, par[100010], eplen[100010], dp[100010][3];
bool past[100010], in_cycle[100010];
vector<int> graph[100010];
stack<int> stk;
vector<int> cycle;

void dfs(int v, int p){
	past[v] = true;
	stk.push(v);
	for (int u : graph[v]){
		if (u == p) continue;
		if (past[u]){
			int x;
			while (x != u){
				x = stk.top();
				cycle.push_back(x);
				stk.pop();
			}
			continue;
		}
		dfs(u, v);
	}
}

int solve(int v, int d, int p){
	if (dp[v][d] != -1) return dp[v][d];
	int &ans = dp[v][d] = 1;
	if (d == 0){
		for (int u : graph[v]){
			ans *= solve(u, 0, v);
		}
		int ans2 = 1;
		for (int u : graph[v]){
			ans2 *= solve(u, 1, v);
		}
		ans += ans2;
	}
	else if (d == 1){
		for (int u : graph[v]){
			ans *= solve(u, 0, v);
		}
		int ans2 = 1;
		for (int u : graph[v]){
			ans2 *= (solve(u, 1, v) + solve(u, 2, v));
		}
		int to_sub = 1;
		for (int u : graph[v]){
			to_sub *= solve(u, 1, v);
		}
		ans += ans2 - to_sub;
	}
	else if (d == 2){
		for (int u : graph[v]){
			if (in_cycle[u] || u == p) continue;
			ans *= solve(u, 0, v);
		}
		if (graph[v].size() == 0)
			ans = 0;
	}
	return ans;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(`0);
	for (int i=0; i<100010; ++i)
		for (int j=0; j<3; ++j)
			dp[i][j] = -1;

	cin >> N;
	for (int i=1; i<=N; ++i)
		cin >> eplen[i];
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		graph[i].push_back(x);
		graph[x].push_back(i);
	}
	for (int i=1; i<=N; ++i){
		if (!past[i]){
			dfs(i, -1);
			stk.clear();
			for (int v : V){
				in_cycle[v] = true;
			}
			for (int v : V){
				solve(v, 0);
				solve(v, 1);
				solve(v, 2);
			}


			for (int i=1; i)



			V.clear();
		}
	}

	return 0;
}