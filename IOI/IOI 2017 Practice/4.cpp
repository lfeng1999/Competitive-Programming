#include <bits/stdc++.h>

using namespace std;

const int mult = 100;
int N;
int g[mult][mult], ans[mult][mult];
bool past[mult*mult*mult], past2[2*mult*mult*mult];
vector<int> graph[2*mult*mult*mult];

stack<int> stk;
void dfs(int v){
	if (past2[v]) return;
	past2[v] = true;
	for (int u : graph[v]){
		dfs(u);
	}
	stk.push(v);
}


int main(){
	freopen("01.in","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N; N *= N;
	for (int i=1; i<=N; ++i){
		for (int j=1; j<=N; ++j){
			cin >> g[i][j];
		}
	}
	for (int i=1; i<=N; ++i){ //single square
		for (int j=1; j<=N; ++j){
			for (int v1=1; v1 <= N; ++v1){
				for (int v2=v1+1; v2 <= N; ++v2){
					graph[mult*mult*mult + i*mult*mult + j*mult + v1].push_back(i*mult*mult + j*mult + v2);
					graph[mult*mult*mult + i*mult*mult + j*mult + v2].push_back(i*mult*mult + j*mult + v1);
				}
			}
		}
	} 
	for (int i=1; i<=N; ++i){ //column
		for (int v=1; v<=N; ++v){
			for (int j1=1; j1<=N; ++j1){
				for (int j2=j1+1; j2<=N; ++j2){
					graph[mult*mult*mult + i*mult*mult + j1*mult + v].push_back(i*mult*mult + j2*mult + v);
					graph[mult*mult*mult + i*mult*mult + j2*mult + v].push_back(i*mult*mult + j1*mult + v);
				}
			}
		}
	}
	for (int j=1; j<=N; ++j){ //row
		for (int v=1; v<=N; ++v){
			for (int i1=1; i1<=N; ++i1){
				for (int i2=i1+1; i2<=N; ++i2){
					graph[mult*mult*mult + i1*mult*mult + j*mult + v].push_back(i2*mult*mult + j*mult + v);

					graph[mult*mult*mult + i2*mult*mult + j*mult + v].push_back(i1*mult*mult + j*mult + v);
				}
			}
		}
	}


	for (int i=1; i<=N; ++i){
		for (int j=1; j<=N; ++j){
			if (g[i][j]){
				int v = mult*mult*mult + i*mult*mult + j*mult + g[i][j];
				dfs(v);
			}
		}
	}

	while (!stk.empty()){
		int v = stk.top();
		int val = v%mult; v /= mult;
		int c = v%mult; v /= mult;
		int r = v%mult; v /= mult;
		stk.pop();
		if (ans[r][c]) continue;
		ans[r][c] = g[r][c];
		if (past[r*mult*mult + c*mult + val]) continue;
		past[r*mult*mult + c*mult + val] = true;
		if (v == 0) ans[r][c] = val;
	}
	for (int i=1; i<=N; ++i){
		for (int j=1; j<=N; ++j){
			cout << ans[i][j] << " ";
		}
		cout << '\n';
	}

	return 0;
}