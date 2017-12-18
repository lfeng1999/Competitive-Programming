#include <bits/stdc++.h>

using namespace std;

int n, nq, curans, state = 0, cyc, alledges[1000010][2], nedges = 0;

struct DisjointSet{
	int root[1000010], rnk[1000010], sz[1000010], edges[1000010], rem;
	bool valid;
	void setup(){
		for (int i=0; i<1000010; ++i){
			root[i] = i;
			rnk[i] = 1;
			sz[i] = 1;
		}
		valid = true;
	}
	void merge(int v, int u){
		edges[v]++; edges[u]++;
		if (edges[v] > 2 || edges[u] > 2) valid = false;

		//now merge
		v = find(v); u = find(u);
		if (v == u){
			valid = false;
			return;
		}
		if (rnk[v] > rnk[u]) swap(v, u);
		root[v] = u;

		sz[u] += sz[v];
		
		if (rnk[v] == rnk[u]) rnk[u]++;
	}
	int find(int v){
		if (v == root[v]) return v;
		return root[v] = find(root[v]);
	}
} dsu[4], ds;

int CountCritical(){
	if (state == 0){
		return n;
	}
	else if (state == 1){
		return ds.sz[ds.find(cyc)];
	}
	else if (state == 2){ //maybe something
		int ret = 0;
		for (int i=0; i<4; ++i){
			if (dsu[i].valid) ret++;
		}
		return ret;
	}
	else if (state == 3){ //nothing
		return 0;
	}
}

void setup_dsu(int v){
	dsu[0].rem = v;
	int t = 1;
	for (int i=0; i<nedges; ++i){
		if (alledges[i][0] == v){
			dsu[t++].rem = alledges[i][1];
		}
		else if (alledges[i][1] == v){
			dsu[t++].rem = alledges[i][0];
		}
	}
	for (int i=0; i<nedges; ++i){
		for (int j=0; j<4; ++j){
			if (alledges[i][0] == dsu[j].rem || alledges[i][1] == dsu[j].rem) continue;
			dsu[j].merge(alledges[i][0], alledges[i][1]);
		}
	}

}
void Link(int v, int u){
	if (ds.edges[v] < ds.edges[u]) swap(v, u);
	if (state == 0){
		if (ds.edges[v] == 2){
			//do a dsu for each of its neighbors
			setup_dsu(v);
			state = 2;
		}
		else if (ds.find(v) == ds.find(u)){
			cyc = v;
			state = 1;
		}
		ds.merge(v, u);
	}
	else if (state == 2){ //3 of something
		for (int i=0; i<4; ++i){
			if (v != dsu[i].rem && u != dsu[i].rem){
				dsu[i].merge(v, u);
			}
		}
	}
	else if (state == 1){ //cycle
		if (ds.edges[v] == 2){
			setup_dsu(v);
			state = 2;
		}
		else{
			if (ds.find(v) == ds.find(u)){
				state = 3;
			}
		}
		ds.merge(v, u);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nq;
	ds.setup();
	for (int i=0; i<4; ++i) dsu[i].setup();

	for (int qq=0; qq<nq; ++qq){
		int v; cin >> v;
		if (v == -1){
			cout << CountCritical() << '\n';
			continue;
		}
		int u; cin >> u;
		alledges[nedges][0] = v, alledges[nedges][1] = u;
		nedges++;
		Link(v, u);
	}


	return 0;
}