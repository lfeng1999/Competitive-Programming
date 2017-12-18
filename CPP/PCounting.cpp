#include <bits/stdc++.h>

using namespace std;

int N, vcnt = 0, ans[100010], to[100010], from[100010];
vector<pair<int,int>> V;
vector<int> graph[100010];
bool past[100010];

void dfs(int v, int p){
	past[v] = true;
	to[v] = ++vcnt;
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
	}
	from[v] = vcnt;
}

int bit[100010];

void update(int i){
	for (; i < 100010; i += i&(-i))
		bit[i]++;
}
int query(int i){
	int tot = 0;
	for (; i > 0; i -= i&(-i))
		tot += bit[i];
	return tot;
}

int main(){
	freopen("promote.in","r",stdin);
	freopen("promote.out","w",stdout);
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=1; i<=N; ++i){
		int p; cin >> p;
		V.push_back(make_pair(p, i));
	}
	for (int i=2; i<=N; ++i){
		int p; cin >> p; 
		graph[p].push_back(i);
	}
	dfs(1, -1);
	sort(V.begin(), V.end());
	reverse(V.begin(), V.end());
	for (pair<int,int> E : V){
		int v = E.second;
		ans[v] = query(from[v]) - query(to[v]);
		update(to[v]);
	}
	for (int i=1; i<=N; ++i){
		cout << ans[i] << "\n";
	}

	return 0;
}