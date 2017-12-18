#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX_N = 100010;
ll dist[MAX_N], ans[MAX_N], gas_cost[MAX_N], N;
int order[MAX_N], rev_order[MAX_N];
vector<pair<int,int>> graph[MAX_N];

void dfs(int v){
	for (pair<int,int> E : graph[v]){
		int u = E.first, d = E.second;
		dist[u] = dist[v] + d;
		dfs(u);
	}
}


struct Node{
	int L, R, pos;
	ll val, dist, gcost = 1e9; 
} seg[300010];

void build_tree(int v, int L, int R){
	seg[v].L = L, seg[v].R = R;
	if (L == R){
		seg[v].pos = order[L];
		seg[v].dist = dist[order[L]];
		return;
	}
	build_tree(v*2, L, (L+R)/2);
	build_tree(v*2+1, (L+R)/2 + 1, R);
}

void update(int v, int pos){
	int L = seg[v].L, R = seg[v].R;
	if (L == R){
		seg[v].gcost = gas_cost[order[pos]];
		return;
	}
	if (pos <= (L+R)/2) 
		update(v*2, pos);
	else
		update(v*2+1, pos);
	seg[v].gcost = min(seg[v*2].gcost, seg[v*2+1].gcost);
}

int query(int v, int gcost){ //What i really care about is the node
	int L = seg[v].L, R = seg[v].R;
	if (L == R){
		return v;
	}

	if (seg[v*2+1].gcost < gcost) return query(v*2+1, gcost);
	else return query(v*2, gcost);
}

void solve(int v){

	int pos = query(1, gas_cost[v]);

	ans[v] = ans[seg[pos].pos] + (dist[v] - dist[seg[pos].pos])*gas_cost[v];

	update(1, rev_order[v]);


	for (pair<int,int> E : graph[v]){
		int u = E.first, d = E.second;
		solve(u);
	}

	gas_cost[v] = 1e9;
	update(1, rev_order[v]);

}


int main(){
	// freopen("TLE.txt","r",stdin);
	// freopen("TLE.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N;

	for (int v=1; v<=N-1; ++v){
		int u, d, c;
		cin >> u >> d >> c;
		graph[u].push_back(make_pair(v, d));
		gas_cost[v] = c;
	}
	dfs(N);
	for (int i=1; i<=N; ++i){
		order[i] = i;
	}

	sort(order+1, order+N+1, [](const int &a, const int &b){
		return dist[a] < dist[b];
	});
	//GOING WRONG WAY WTRARJIAEK order[a] = b means the a-th smallest dist is at b
	
	for (int v=1; v<=N; ++v){
		rev_order[order[v]] = v;
	}
	build_tree(1, 1, N);
	update(1, 1);

	solve(N);

	for (int v=1; v<N; ++v){
		cout << ans[v] << '\n';
	}

	return 0;
}