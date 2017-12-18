#include <bits/stdc++.h>

using namespace std;

int ls[1200010], rs[1200010], to_stu[100010], from_stu[100010], root[100010], rnk[100010], sum[1200010], subsz[100010];
int troot[100010], N, M, Q, nxt = 0;

int find(int x){
	if (x == root[x]) return x;
	return root[x] = find(root[x]);
}

void build(int v, int L, int R, int val){
	if (L == R){
		sum[v] = 1;
		return;
	}
	int mid = (L+R)/2;
	if (val <= mid){
		ls[v] = ++nxt;
		build(ls[v], L, mid, val);
	}
	else{
		rs[v] = ++nxt;
		build(rs[v], mid+1, R, val);
	}
	sum[v] = sum[ls[v]] + sum[rs[v]];
}

int merge(int v, int u){
	if (!v) return u;
	if (!u) return v;

	ls[v] = merge(ls[v], ls[u]);
	rs[v] = merge(rs[v], rs[u]);

	sum[v] = sum[ls[v]] + sum[rs[v]];
	return v;
}

void mergeset(int v, int u){
	v = find(v);
	u = find(u);
	if (v == u)
		return;
	if (subsz[v] < subsz[u])
		swap(v, u);
	subsz[v] += subsz[u];
	root[u] = v;
	merge(troot[v], troot[u]);
}

int query(int v, int L, int R, int val){
	if (L == R)
		return v;
	int mid = (L+R)/2;
	if (sum[ls[v]] >= val)
		return query(ls[v], L, mid, val);
	else
		return query(rs[v], mid+1, R, val - sum[ls[v]]);
}


int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		to_stu[x] = i;
		from_stu[i] = x;
	}
	for (int i=0; i<M; ++i){
		int v, u; cin >> v >> u;
		mergeset(v, u);
	}
	cin >> Q;
	for (int i=0; i<Q; ++i){
		char ch; int a, b;
		cin >> ch >> a >> b;
		if (ch == 'B'){
			merge(a, b);
		}
		else{
			int v = find(a);
			if (subsz[v] < b){
				cout << -1 << '\n';
				continue;
			}

			cout << to_stu[query(troot[v], 1, N, b)] << '\n';
		}
	}

	return 0;
}