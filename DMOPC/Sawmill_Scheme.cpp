#include <bits/stdc++.h>

using namespace std;

vector<int> graph[1000010];
double ans[1000010];

int main(){
	//freopen("test.txt","r",stdin);
	ans[1] = 1;
	int N, M; cin >> N >> M;
	for (int i=0; i<M; ++i){
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
	}
	for (int v=1; v<=N; ++v){
		for (int i=0; i<graph[v].size(); ++i){
			int u = graph[v][i];
			ans[u] += ans[v] / (double)graph[v].size();
		}
	}
	for (int v=1; v<=N; ++v){
		if (graph[v].size() == 0){
			printf("%.10f\n", ans[v]);
		}
	}


	return 0;
}