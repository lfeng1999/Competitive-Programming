#include <bits/stdc++.h>

using namespace std;

vector<int> graph[1010];
int N, M;
vector<int> groups[1010][2]; 
bool past[1010];
int nGroup = 0, xGroup[1010], dist[1010];
bool is_impossible = false, dp[1010][2010];
vector<int> nGraph[2100000];

vector<int> ans[2010];
vector<int> stk;
bool past2[1010][2010];

void solve(int g, int v){
	past2[g][v] = true;
	if (g == nGroup){
		ans[v] = stk;
		return;
	}
	if (!past2[g+1][v+dist[g+1]]){
		stk.push_back(0);
		solve(g+1, v + dist[g+1]);
		stk.pop_back();
	}
	if (!past2[g+1][v-dist[g+1]]){
		stk.push_back(1);
		solve(g+1, v - dist[g+1]);
		stk.pop_back();
	}
}

void dfs(int v, int i){
	past[v] = true;
	groups[nGroup][i].push_back(v);
	xGroup[v] = i;
	for (int u : graph[v]){
		if (past[u]){
			if (xGroup[u] == i)
				is_impossible = true;
			continue;
		}
		dfs(u, i^1);
	}
}

int studentgroup[1010];

void expand(vector<int> ans){

	for (int i=0; i<ans.size(); ++i){
		for (int v : groups[i+1][ans[i]])
			studentgroup[v] = 1;
		for (int v : groups[i+1][1^ans[i]])
			studentgroup[v] = 2;
	}
	for (int i=1; i<=N; ++i){
		cout << studentgroup[i];
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i=0; i<M; ++i){
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	for (int i=1; i<=N; ++i){
		if (past[i]) continue;
		nGroup++;
		dfs(i, 0);
		dist[nGroup] = groups[nGroup][0].size() - groups[nGroup][1].size();
		// cout << dist[nGroup] << endl;
	}
	if (is_impossible){
		cout << -1;
		return 0;
	}
	dp[0][1000] = true;
	solve(0, 1000);
	// memset(past2, false, sizeof(past2));

	for (int i=0; i<1000; ++i){
		int a = 1000 - i, b = 1000 + i;
		vector<int> fin_ans;
		if (past2[nGroup][a] && past2[nGroup][b]){
			if (lexicographical_compare(ans[a].begin(), ans[a].end(), ans[b].begin(), ans[b].end())){
				fin_ans = ans[a];
			}
			else{
				fin_ans = ans[b];
			}
		}
		else if (past2[nGroup][a]){
			fin_ans = ans[a];
		}
		else if (past2[nGroup][b]){
			fin_ans = ans[b];
		}
		if (past2[nGroup][a] || past2[nGroup][b]){
			expand(fin_ans);
			return 0;
		}
	}	



	return 0;
}