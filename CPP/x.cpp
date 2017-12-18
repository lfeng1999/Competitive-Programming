#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> graph[10010];
bool past[10010];

void dfs(int v){
	past[v] = true;
	for (int u :graph[v]){
		if (!past[u])
			dfs(u);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		int x; cin >> x;
		graph[i].push_back(x);
		graph[x].push_back(i);
	}
	int cnt = 0;
	for (int i=1; i<=n; ++i){
		if (!past[i]){
			dfs(i);
			cnt++;
		}
	}
	cout << cnt;
	return 0;
}