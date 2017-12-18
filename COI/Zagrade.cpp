#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
vector<int> graph[300010];
char a[300010];
bool usedc[300010];
int n;
int msz[300010], sz[300010];

stack<int> stk;
void dfs(int v, int p){
	stk.push(v);
	sz[v] = 1;
	msz[v] = 0;
	for (int u : graph[v]){
		if (u == p || usedc[u]) continue;
		dfs(u, v);
		sz[v] += sz[u];
		msz[v] = max(sz[u], msz[v]);
	}
}

int get_center(int rt){
	dfs(rt, rt);
	int cur = 1e9, ret = 0;
	while (!stk.empty()){
		int v = stk.top(); stk.pop();
		msz[v] = max(msz[v], sz[rt] - sz[v]);
		if (msz[v] < cur){
			cur = msz[v];
			ret = v;
		}
	}
	return ret;
}
int cnt[300010];

void dfs2(int v, int p, vector<int> &V, int dep, int mdep){ //solves left
	// cout << v << " " << dep << " " << a[v] << endl;
	if (a[v] == '(') dep++;
	else dep--;
	mdep = max(mdep, dep);
	if (dep == mdep) V.push_back(dep);

	for (int u : graph[v]){
		if (u == p || usedc[u]) continue;
		dfs2(u, v, V, dep, mdep);
	}
}
void dfs3(int v, int p, vector<int> &V, int dep, int mdep){ //solves right
	if (a[v] == ')') dep++;
	else dep--;
	mdep = max(mdep, dep);
	if (dep == mdep)
		V.push_back(dep);
	for (int u : graph[v]){
		if (u == p || usedc[u]) continue;
		dfs3(u, v, V, dep, mdep);
	}
}
lint solve(vector<int> &l, vector<int> &r){
	lint ret = 0;
	for (int x : l) cnt[x]++;
	for (int x : r) ret += cnt[x];
	for (int x : l) cnt[x]--;
	return ret;
}

lint solve(int v){
	vector<int> l, r;
	lint ret = 0;
	for (int u : graph[v]){
		if (usedc[u]) continue;
		vector<int> tl, tr;
		if (a[v] == '(')
			dfs2(u, v, tl, 1, 1);
		else if (a[v] == ')')
			dfs2(u, v, tl, -1, 0);
		dfs3(u, v, tr, 0, 0);
		ret -= solve(tl, tr);

		for (int x : tl) l.push_back(x);
		for (int x : tr) r.push_back(x);
		for (int x : tl){
			if (x == 0) ret++;
		}
		for (int x : tr){
			if (a[v] == '(' && x == 1) ret++;
		}
	}
	ret += solve(l, r);
	return ret;
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> a[i];
	}
	for (int i=0; i<n-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u); graph[u].push_back(v);
	}
	queue<int> Q;
	Q.push(1);
	lint ans = 0;
	while (!Q.empty()){
		int v = Q.front(); Q.pop();
		v = get_center(v);
		usedc[v] = true;
		ans += solve(v);
		for (int u : graph[v]){
			if (!usedc[u]) Q.push(u);
		}
	}
	cout << ans;


	return 0;
}