#include <bits/stdc++.h>

using namespace std;

vector<int> graph[100010];
int c[100010], N, nfailed[100010];
int pst[100010][2], ncol[100010], ncolv[100010];

void dfs(int v, int p){
	set<int> S;
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
		if (ncolv[u] > 1){
			ncol[v] = 2;
		}
		if (c[u] != c[v]){
			S.insert(c[u]);
		}
	}
	ncolv[v] = 1 + ncol[v] + S.size();
}
bool fk = false;
int pos = 0;

void dfs2(int v, int p){
	int nfail = 0;
	for (int u : graph[v]){
		if (u == p) continue;
		if (isfailed[u])
			nfail++;
	}
	if (nfail == 0){
		fk = true;
		pos = v;
		return;
	}
	if (nfail == 1){
		for (int u : graph[v]){
			if (u == p) continue;
			if (isfailed[u]){
				dfs2(u, v);
			}
		}
	}
}
int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<N-1; ++i){
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	for (int i=1;i<=N; ++i){
		cin >> c[i];
	}
	dfs(1, -1);
	dfs2(1, -1);
	if (fk){
		cout << "YES" << endl;
		cout << pos;
	}
	else{
		cout << "NO";
	}
	return 0;
}