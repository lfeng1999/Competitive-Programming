#include <bits/stdc++.h>

using namespace std;

vector<int> graph[200010];
set<int> S[2];
int N, M, K, t = 1;
char cmd[200010];
int ans[200010], val[200010];

void dfs(int v){

	ans[v] = S[t].size();
	if (cmd[v] == 'X'){
		t ^= 1;
		dfs(v+1);
		t ^= 1;
	}
	else if (cmd[v] == 'F'){
		bool flag = S[1^t].count(val[v]);
		if (flag){
			S[1^t].erase(val[v]);
			S[t].insert(val[v]);
		}
		dfs(v+1);
		if (flag){
			S[1^t].insert(val[v]);
			S[t].erase(val[v]);
		}
	}
	else if (cmd[v] == 'D'){
		bool flag = S[t].count(val[v]);
		if (flag){
			S[t].erase(val[v]);
			S[1^t].insert(val[v]);
		}
		dfs(v+1);
		if (flag){
			S[t].insert(val[v]);
			S[1^t].erase(val[v]);
		}
	}
	for (int u : graph[v]){
		dfs(u);
	}
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;
	for (int i=1; i<=N; ++i){
		S[0].insert(i);
	}
	for (int i=1; i<=M; ++i){
		cin >> cmd[i-1];
		if (cmd[i-1] == 'X') continue;
		int x; cin >> val[i-1];

		if (cmd[i-1] == 'R'){
			graph[x].push_back(i);
		}
	}
	dfs(0);

	set<pair<int,int>> Q;

	for (int i=1; i<=M; ++i){
		Q.insert(make_pair(ans[i], i));
		if (i > K)
			Q.erase(make_pair(ans[i-K], i-K));
		cout << ans[i] << " " << (*(--Q.end())).first << '\n';
	}

	return 0;
}