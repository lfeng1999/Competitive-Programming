// Dominator Tree for a dag... the idea is similar to articulation points.
// It stores only the necessary points. The points where if u removed it, it would disconnect the nodes below it from the Directed Graph
// USes DSU + DFS
// https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
#include <bits/stdc++.h>

using namespace std;

vector<int> graph[100010], rgraph[100010], dtree[1000010];
int disc[100010], rdisc[100010], t = 0, par[100010];
int semidom[100010], dom[100010], idom[100010];
// semidom is the highest node where there is a direct path other than using the dfs tree
// to v that uses other branches of the dfs tree + extra edges... mostly (Default is parent)


void dfs(int v){ //makes directed graph into a tree
	disc[v] = ++t; rdisc[t] = v; //reordering nodes
	for (int u : graph[v]){
		if (disc[u] == 0){
			dfs(u);
			par[u] = v; //generate the dfs tree
		}
	}
}

int root[100010], rnk[100010]; //DSU part
//root is well root of the dynamic forests, rnk is the point in the disjoint set with the smallest semidom[]
int label[100010];
//label is the legit shit. It stores the point with the lowest semidom in the forest

int find(int v, int x = 0){ //log(n) path compression
	//Why can't we take the thing at the top of the forest?
	//Because we didn't touch that node yet. it's a placeholder.... e.g.) root[i] = par[i].... but if we do
	//find(i) it shouldn't give us par[i]'s value.. because we haven't calculated it yet.
	//If we have calculated par[i], there'll be a par[par[i]] or root[par[i]] will exist, so we can use par[i]'s semidom[] value
	if (v == root[v]){
		if (x == 0) return v; //only one thing in forest (haven't done calculations yet)
		else return -1; //otherwise, don't take the thing at the top of the forest... we're adding to the top of the forest
	}
	int u = find(root[v], x+1);
	if (u < 0) //don't use the top node in the forest
		return v;
	if (semidom[label[v]] > semidom[label[root[v]]]){
		label[v] = label[root[v]]; //root[v]'s label was already updated to the best
	}
	root[v] = u; 
	if (x == 0){
		return label[v]; //return the point from the root -> v that gives the smallest semidom....
	}
	return u; //this only helps to do path compression. The real magic is in label
}

vector<int> bucket[100010];

void solve() {
	// freopen("test.txt","r",stdin);
	// cin.sync_with_stdio(0); cin.tie(0);
	int N, M; cin >> N >> M;
	for (int i=0; i<M; ++i){ //directed graph
		int v, u; cin >> v >> u;
		graph[v].push_back(u);
		rgraph[u].push_back(v); //reverse directed graph
	}
	dfs(1);
	for (int i=1; i<=N; ++i){
		root[i] = i;
		rnk[i] = i;
		semidom[i] = i; 
		label[i] = i;
	}
	for (int i=N; i>=1; --i){
		for (int u : rgraph[i]){
			semidom[i] = min(semidom[i], semidom[find(u)]);
		}
		if (i > 1) bucket[semidom[i]].push_back(i);
		
		for (int v : bucket[i]){
			int p = find(v);
			if (semidom[v] == semidom[p]){
				dom[v] = semidom[v];
			}
			else{
				dom[v] = p; //refer to website for logic
			}
		}
		root[i] = par[i]; //this constructs the forest for this branch to use later.... starting from the bottom up
	}
	for (int i=2; i<=N; ++i){
		if (dom[i] != semidom[i])
			dom[i] = dom[dom[i]]; //gives the dominator
		tree[rdisc[dom[i]]].push_back(rdisc[i]); //remember, we renumbered the points on the graph....
	}

	return;
}