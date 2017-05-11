#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Edge{
	int v, u, d, i, nv, nu;
	bool operator < (const Edge &a) const{
		return d < a.d;
	}
} edg[50010];

struct edgecmp{
	bool operator() (const int &i, const int &j) const{
		if (edg[i].d == edg[j].d)
			return i < j;
		return edg[i].d < edg[j].d;
	}
};

set<int, edgecmp> edges;
int N, M, Q;
int root[20010], rnk[20010];
int bsize, nblocks;
int queries[50010][2];
bool modified[50010], modifiednode[20010];
vector<Edge> mst;

int find(int v){
	if (root[v] == v)
		return v;
	return root[v] = find(root[v]);
}

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> Q;

	for (int i=1; i<=M; ++i){
		cin >> edg[i].v >> edg[i].u >> edg[i].d;
		edg[i].i = i;
		edges.insert(i);
	}
	bsize = sqrt(Q);
	nblocks = (Q-1)/bsize + 1;

	for (int i=0; i<Q; ++i){
		cin >> queries[i][0] >> queries[i][1];
	}
	for (int k=0; k<nblocks; ++k){
		int L = k*bsize, R = (k+1)*bsize - 1;
		R = min(R, Q - 1);

		for (int i=1; i<=N; ++i){
			rnk[i] = 1;
			root[i] = i;
		}
		set<int> cmst; //compressed nodes
		for (int i=L; i<=R; ++i){
			int p = queries[i][0];
			modified[p] = true;
			modifiednode[edg[p].v] = modifiednode[edg[p].u] = true;
			rnk[edg[p].v] = 1e5;
			rnk[edg[p].u] = 1e5;
		}
		for (int i=1; i<=N; ++i){
			if (modifiednode[i]){
				cmst.insert(i);
			}
		}
		ll forest = 0;
		for (int pp : edges){
			Edge &E = edg[pp];
			int v = E.v, u = E.u;
			v = find(v); u = find(u);
			if (v == u)
				continue;
			if (modifiednode[v] && modifiednode[u]){
				continue;
			}
			forest += E.d;
			if (rnk[v] < rnk[u])
				swap(v, u);
			root[u] = v;
			if (rnk[v] == rnk[u])
				rnk[v]++;
		} //forest of sqrt(N) nodes
		for (int i=1; i<=M; ++i){
			edg[i].nv = find(edg[i].v); //new vertex
			edg[i].nu = find(edg[i].u);
		}
		set<int, edgecmp> oldmst;
		for (int pp : edges){
			Edge &E = edg[pp];
			int v = E.nv, u = E.nu;
			v = find(v); u = find(u);
			if (v == u || modified[pp])
				continue;
			oldmst.insert(E.i);
			if (rnk[v] < rnk[u])
				swap(v, u);
			root[u] = v;
			if (rnk[v] == rnk[u])
				rnk[v]++;
		}
		for (int i=1; i<=M; ++i){ //possible edges for the tree
			if (modified[i])
				oldmst.insert(i);
		}
		for (int i=L; i<=R; ++i){ //time to do updates
			for (int pp : cmst){
				rnk[pp] = 1;
				root[pp] = pp;
			}
			int p = queries[i][0], d = queries[i][1];
			oldmst.erase(p);
			edges.erase(p);
			edg[p].d = d;
			oldmst.insert(p);
			edges.insert(p);
			ll curmst = forest;
			for (int id : oldmst){
				Edge &E = edg[id];
				int v = E.nv, u = E.nu;
				v = find(v); u = find(u);
				if (v == u)
					continue;
				curmst += E.d;
				if (rnk[v] < rnk[u])
					swap(v, u);
				root[u] = v;
				if (rnk[v] == rnk[u])
					rnk[v]++;
			}
			printf("%lld\n", curmst);
		}
		for (int i=L; i<=R; ++i){
			int p = queries[i][0];
			modified[p] = false;
			modifiednode[edg[p].v] = modifiednode[edg[p].u] = false;
		}
	}

	return 0;
}