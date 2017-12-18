#include <bits/stdc++.h>

using namespace std;

vector<int> graph[100010];
int N, M, len = 0, dist[100010][2], longest = 0;
bool is_pho[100010];

bool dfs(int v, int p){
	bool flag = is_pho[v];

	// cout << v << " " << p << endl;
	for (int u : graph[v]){
		if (u == p) continue;
		if (dfs(u, v)){
			flag = true;
			len++;
			dist[v][1] = max(dist[v][1], dist[u][0] + 1);
			if (dist[v][0] < dist[v][1])
				swap(dist[v][0], dist[v][1]);
		}
	}
	longest = max(longest, dist[v][0] + dist[v][1]);
	return flag;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N >> M;
	int st = 0;
	for (int i=0; i<M; ++i){
		int x; cin >> x; is_pho[x] = true;
		st = x;
	}
	for (int i=0; i<N-1; ++i){
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(st, -1);
	cout << 2*len - longest;

	return 0;
}