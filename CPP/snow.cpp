#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
vector<pair<int,int>> graph[1010];
int N, M;
pair<int,int> best[1010];

int to[1010], low_cut[1010], vcnt = 0;
bool is_cycle = false, reach_end = false, inq[1010];

bool dfs(int v, int p){
	to[v] = low_cut[v] = ++vcnt;
	if (v == N)
		reach_end = true;
	for (pair<int,int> E : graph[v]){
		int u = E.first;
		if (to[u] != 0)
			low_cut[v] = min(low_cut[v], to[u]);
		else{
			dfs(u, v);
			low_cut[v] = min(low_cut[v], low_cut[u]);
			if (to[v] == low_cut[u]){
				is_cycle = true;
			}
		}
	}
}

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i=0; i<M; ++i){
		int v, u, d; cin >> v >> u >> d;
		graph[v].push_back(make_pair(u, d));
	}
	dfs(1, -1);
	if (is_cycle || !reach_end){
		cout << -1;
		return 0;
	}
	queue<int> Q;
	Q.push(1);
	inq[1] = true;
	best[1] = make_pair(0, 1);
	while (!Q.empty()){
		int v = Q.front();
		Q.pop();
		inq[v] = false;
		for (pair<int,int> E : graph[v]){
			int u = E.first, nd = E.second + best[v].first, ns = 1 + best[v].second;
			if (make_pair(nd, ns) > best[u]){
				best[u] = make_pair(nd, ns);
				if (!inq[u]){
					Q.push(u);
					inq[u] = true;
				}
			}
		}
	}
	cout << best[N].first << " " << best[N].second;

	return 0;
}