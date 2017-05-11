#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

int  n, a[200010], to[200010], from[200010], vcnt = 0;
lint dep[200010], rad;
vector<pair<int,lint>> graph[200010];

class mycomp{
public:
	bool operator () (int a, int b){return dep[a] < dep[b];}
};
struct pqpointer{
	priority_queue<int, vector<int>, mycomp> *Q;
} pq[200010];


void dfs(int v, lint d){
	dep[v] = d;
	for (auto e : graph[v]){
		dfs(e.first, d + e.second);
	}
}


int main(){
	// freopen("test.txt","r",stdin);
	freopen("runaway.in","r",stdin);
	freopen("runaway.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> rad;
	for (int i=2; i<=n; ++i){
		int p; lint len; cin >> p >> len;
		graph[p].push_back({i, len});
	}
	dfs(1, 0);
	for (int v = n; v>=1; --v){
		if (!pq[v].Q) pq[v].Q = new priority_queue<int, vector<int>, mycomp>();
		(*pq[v].Q).push(v);
		for (auto &e : graph[v]){
			int u = e.first;
			if ((*pq[u].Q).size() > (*pq[v].Q).size()){
				swap(pq[u].Q, pq[v].Q);
			}
			while (!(*pq[u].Q).empty()){
				(*pq[v].Q).push((*pq[u].Q).top());
				(*pq[u].Q).pop();
			}
		}
		while (!(*pq[v].Q).empty() && dep[(*pq[v].Q).top()] - dep[v] > rad){
			(*pq[v].Q).pop();
		}
		a[v] = (*pq[v].Q).size();
	}

	for (int i=1; i<=n; ++i){
		cout << a[i] << '\n';
	}
	return 0;
}