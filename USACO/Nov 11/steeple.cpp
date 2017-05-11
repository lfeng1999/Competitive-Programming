#include <bits/stdc++.h>

using namespace std;

const int maxbit = 1010;
vector<pair<int,pair<int,int>>> vlines, hlines;
int n, g[255][255], src = 0, snk;
bool past[255];
int par[255];

int get_flow(){
	queue<int> Q; Q.push(src);
	memset(past, false, sizeof(past));
	while (!Q.empty()){
		int v = Q.front(); Q.pop();
		for (int i=0; i<=n+1; ++i){
			if (past[i] || g[v][i] == 0) continue;
			Q.push(i);
			par[i] = v;
			past[i] = true;
		}
	}
	if (!past[snk]) return 0;
	int v = snk, mflow = 1e9;
	while (v != src){
		mflow = min(mflow, g[par[v]][v]);
		v = par[v];
	}
	v = snk;
	while (v != src){
		g[par[v]][v] -= mflow;
		g[v][par[v]] += mflow;
		v = par[v];
	}
	return mflow;
}

int max_flow(){
	int ret = 0, path = 0;
	do{
		path = get_flow();
		ret += path;
	}while (path != 0);
	return ret;
}

int main(){
	freopen("test.txt","r", stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	snk = n+1;
	for (int i=0; i<n; ++i){
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		if (x1 == x2){
			vlines.push_back(make_pair(x1, make_pair(y1, y2)));
		}
		else if (y1 == y2){
			hlines.push_back(make_pair(y1, make_pair(x1, x2)));
		}
	}
	for (int i=0; i<hlines.size(); ++i){
		g[src][i+1] = 1;
	}
	for (int i=0; i<vlines.size(); ++i){
		g[hlines.size()+i+1][snk] = 1;
	}
	for (int i=0; i<hlines.size(); ++i){
		for (int j=0; j<vlines.size(); ++j){
			int hx1 = hlines[i].second.first, hx2 = hlines[i].second.second, hy = hlines[i].first;
			int vx = vlines[j].first, vy1 = vlines[j].second.first, vy2 = vlines[j].second.second;
			int n1 = i+1, n2 = hlines.size() + j + 1;
			if (hx1 <= vx && vx <= hx2 && vy1 <= hy && hy <= vy2){
				g[n1][n2] = 1;
			}
		}
	}
	cout << n - max_flow();
	return 0;
}