#include <bits/stdc++.h>

using namespace std;

int root[100010], ords[100010], root2[100010], sr[100010], subsz[100010], ordsr[100010];
int op[300010][3], N, M, rnk[100010], rnk2[100010], subsz2[100010];
vector<int> graph[100010];

int find(int v){
	if (v == root[v]) return v;
	return root[v] = find(root[v]);
}

void merge(int v, int u, bool k){
	int rootv = find(v);
	int rootu = find(u);
	if (rootv == rootu)
		return;
	if (rnk[rootv] < rnk[rootu]){
		if (k)
			graph[rootu].push_back(rootv);
		root[rootv] = rootu;
		subsz[rootu] += subsz[rootv];
	}
	else if (rnk[rootu] < rnk[rootv]){
		if (k)
			graph[rootv].push_back(rootu);
		root[rootu] = rootv;
		subsz[rootv] += subsz[rootu];
	}
	else{
		if (k)
			graph[rootu].push_back(rootv);
		root[rootv] = rootu;
		subsz[rootu] += subsz[rootv];
		rnk[rootu]++;
	}
}
int to[100010], from[100010], ncnt = 0;
void dfs(int v){
	++ncnt;
	to[v] = ncnt;
	ords[ncnt] = v;
	ordsr[ncnt] = sr[v];
	for (int u : graph[v]){
		if (to[u] == 0)
			dfs(u);
	}
	from[v] = ncnt;
}

struct Node{
	Node *lef = nullptr, *rig = nullptr;
	int val = 0;
};

Node *build_tree(int L, int R){
	Node *ret = new Node();
	if (L == R){
		return ret;
	}
	int mid = (L+R)/2;
	ret->lef = build_tree(L, mid);
	ret->rig = build_tree(mid+1, R);
	return ret;
}

Node *update(Node *root, int L, int R, int p){
	Node *ret = new Node();

	if (L == R){
		ret->val = 1;
		return ret;
	}
	int mid = (L+R)/2;
	ret->lef = root->lef;
	ret->rig = root->rig;
	if (p <= mid){
		ret->lef = update(root->lef, L, mid, p);
	}
	else{
		ret->rig = update(root->rig, mid+1, R, p);
	}
	ret->val = ret->lef->val + ret->rig->val;
	return ret;
}

int query(Node* lef, Node* rig, int L, int R, int val){
	if (L == R){
		return L;
	}
	int mid = (L+R)/2, ldiff = rig->lef->val - lef->lef->val;
	if (ldiff >= val){
		return query(lef->lef, rig->lef, L, mid, val);
	}
	else{
		return query(lef->rig, rig->rig, mid+1, R, val - ldiff);
	}
}

int revM[100010];

Node *roots[100010];

pair<char,pair<int,int>> V[300010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i=1; i<=N; ++i){
		cin >> sr[i];
		revM[sr[i]] = i;
		root[i] = i;
		subsz[i] = 1;
	}
	for (int i=0; i<M; ++i){
		int v, u; cin >> v >> u;
		merge(v, u, true);
	}
	for (int i=1; i<=N; ++i){
		root2[i] = root[i];
		rnk2[i] = rnk[i];
		subsz2[i] = subsz[i];
	}
	int Q;
	cin >> Q;
	for (int i=1; i<=Q; ++i){
		char ch; int a, b;
		cin >> ch >> a >> b;
		V[i-1] = make_pair(ch, make_pair(a, b));
		if (ch == 'B'){
			merge(a, b, true);
		}
	}
	for (int i=1; i<=N; ++i){
		if (root[i] == i){
			dfs(i);
		}
	}
	for (int i=1; i<=N; ++i){
		root[i] = root2[i];
		rnk[i] = rnk2[i];
		subsz[i] = subsz2[i];
	}

	roots[0] = build_tree(1, N);
	for (int i=1; i<=N; ++i){
		roots[i] = update(roots[i-1], 1, N, ordsr[i]);
	}
	for (int i=0; i<Q; ++i){
		char ch = V[i].first; int a = V[i].second.first, b = V[i].second.second;
		if (ch == 'B'){
			merge(a, b, false);
		}
		else{
			int rootv = find(a);
			if (subsz[rootv] < b){
				cout << -1 <<  '\n';
				continue;
			}
			cout << revM[query(roots[to[rootv] - 1], roots[to[rootv] + subsz[rootv] - 1], 1, N, b)] << '\n';
		}
	}
	return 0;
}