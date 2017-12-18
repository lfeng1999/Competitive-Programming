#include <bits/stdc++.h>

using namespace std;

int N, M, a[1010][1010], b[1010][1010], p[1000010], lis[1010], rsize[1010];
vector<int> graph[1010];
bool past[1010];
stack<int> stk;

void dfs(int v){
	past[v] = true;
	for (int u : graph[v]){
		if (!past[u])
			dfs(u);
	}
	stk.push(v);
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;

	int fk = 0;
	for (int i=0; i<N; ++i){
		for (int j=0; j<M; ++j){
			cin >> a[i][j];
			p[a[i][j]] = i*M + j;
			if (a[i][j] != 0)
				rsize[i]++;
			
		}
	}
	bool is_filled = true, is_same = true;
	for (int i=0; i<N; ++i){
		for (int j=0; j<M; ++j){
			cin >> b[i][j];
			if (b[i][j] == 0)
				is_filled = false;
			if (a[i][j] != b[i][j])
				is_same = false;
		}
	}
	if (is_filled && !is_same){
		cout << -1;
		return 0;
	}
	int ans = 0;
	for (int i=0; i<N; ++i){
		set<int> S;
		int cnt = 0;
		for (int j=0; j<M; ++j){
			if (b[i][j] == 0)
				continue;
			int nr = p[b[i][j]]/M;
			if (nr == i){
				int x = p[b[i][j]]%M;
				auto it = S.upper_bound(x);
				if (it != S.end())
					S.erase(it);
				S.insert(x);
			}
			else{ //Create the connections
				graph[i].push_back(nr);
				graph[nr].push_back(i);
			}
		}
		lis[i] = S.size();
	}
	for (int i=0; i<N; ++i){
		if (past[i]) continue;
		dfs(i);
		bool is_missing = false;
		while (!stk.empty()){
			int v = stk.top();
			stk.pop();
			if (rsize[v] != M || rsize[v] == lis[v])
				is_missing = true;
			ans += rsize[v] - lis[v];
		}
		if (!is_missing)
			ans++;
	}
	cout << ans;

	return 0;
}