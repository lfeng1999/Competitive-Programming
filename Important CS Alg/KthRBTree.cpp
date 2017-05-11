#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAXN = 100010;
int N, M, root[MAXN], to_stu[MAXN], from_stu[MAXN];
ordered_set<int> os[MAXN];

int find(int x){
	if (root[x] == x) return x;
	return root[x] = find(root[x]);
}

void merge(int v, int u){
	v = find(v);
	u = find(u);
	if (v == u)
		return;
	if (os[v].size() < os[u].size())
		swap(v, u);
	
	root[u] = v;
	for (int x : os[u]){
		os[v].insert(x);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		from_stu[i] = x;
		to_stu[x] = i;
		os[i].insert(x);
		root[i] = i;
	}
	for (int i=0; i<M; ++i){
		int v, u; cin >> v >> u;
		merge(v, u);
	}
	int Q;
	cin >> Q;
	for (int i=0; i<Q; ++i){
		char ch; int a, b;
		cin >> ch >> a >> b;
		if (ch == 'B'){
			merge(a, b);
		}
		else{
			int rootv = find(a);
			if (b > os[rootv].size()){
				cout << -1 << '\n';
				continue;
			}
			cout << to_stu[*os[rootv].find_by_order(b-1)] << '\n';
		}
	}
	return 0;
}