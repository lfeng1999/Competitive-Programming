#include <bits/stdc++.h>

using namespace std;


int n, nedge, ngrp, snk;
int nxt[150010][2];
bool past[150010][2];
pair<int,int> to[150010][2];

pair<int,int> dfs(int v, int p){
	if (p != nxt[v][0]) p = 1;
	else p = 0;
	if (to[v][p] != make_pair((int)-1e9, 0)) return to[v][p];
	to[v][p] = make_pair(-1e8, 0);
	pair<int,int> cur;
	if (nxt[v][1^p] != -1)
		cur = dfs(nxt[v][1^p], v);
	else
		cur = dfs(nxt[v][0], v);

	to[v][p] = make_pair(cur.first + 1, cur.second);
	return to[v][p];
}

bool past2[150010][2];

int distto(int v1, int p1, int v2, int p2){
	memset(past2, false, sizeof(past2));
	int len = 0;
	do{
		if (past2[v1][p1]) return 1e9 + 10;
		len++;
		past2[v1][p1] = true;
		int nv = nxt[v1][1^p1];
		if (nv == -1) nv = nxt[v1][0];
		p1 = v1;
		v1 = nv;
		if (p1 == nxt[v1][0]) p1 = 0;
		else p1 = 1;
	} while (v1 != v2 || p1 != p2);

	return len;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nedge >> snk;
	for (int i=0; i<n; ++i){
		nxt[i][0] = nxt[i][1] = -1;
		to[i][0] = to[i][1] = make_pair(-1e9, 0);
	}
	to[snk][0] = make_pair(0, 0);
	to[snk][1] = make_pair(0, 1);
	for (int qq=0; qq<nedge; ++qq){
		int v, u; cin >> v >> u;
		
		if (nxt[v][0] == -1) nxt[v][0] = u;
		else if (nxt[v][1] == -1) nxt[v][1] = u;

		if (nxt[u][0] == -1) nxt[u][0] = v;
		else if (nxt[u][1] == -1) nxt[u][1] = v;
	}
	for (int v = 0; v < n; ++v){
		dfs(v, 1e9);
	}
	int d01 = distto(snk, 0, snk, 1); //0 to 1
	int d10 = distto(snk, 1, snk, 0); //1 to 0
	int d00 = distto(snk, 0, snk, 0); //0 to 1
	int d11 = distto(snk, 1, snk, 1); //1 to 0
	// cout << d00 << " " << d01 << " " << d10 << " " << d11 << endl;
	d00 = min(d00, d01 + d10);
	d11 = min(d11, d10 + d01);
	cin >> ngrp;
	for (int qq=0; qq<ngrp; ++qq){
		int x; cin >> x;
		int ans = 0;
		for (int i=0; i<n; ++i){
			if (to[i][1].first < 0) continue;
			int l1 = x - to[i][1].first, typ = to[i][1].second;
			if (l1 < 0) continue;
			if (typ == 0){
				if (l1 % d00 == 0){
					ans++;
				}
				else if (l1 >= d01 && (l1 - d01)%d11 == 0){
					ans++;
				}
			}
			else if (typ == 1){
				if (l1 % d11 == 0){
					ans++;
				}
				else if (l1 >= d10 && (l1 - d10)%d00 == 0){
					ans++;
				}
			}
		}
		cout << ans << ' ';
	}
	return 0;
}