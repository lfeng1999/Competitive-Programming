#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct Event{
	lint t; int typ, v;
	Event(lint _t, int _typ, int _v) : t(_t), typ(_typ), v(_v){}
	bool operator < (const Event &a) const{
		if (t != a.t) return t > a.t;
		return typ < a.typ;
	}
	//1 is add, 2 is remove, 3 is query
};

struct SegmentTree{
	int seg[600010];
	void reset(){memset(seg, 0, sizeof(seg));}
	void flip(int v, int L, int R, int p){
		if (L == R) {seg[v] ^= 1; return;}
		if (p <= (L+R)/2) flip(v*2, L, (L+R)/2, p);
		else flip(v*2+1, (L+R)/2+1, R, p);
		seg[v] = seg[v*2] + seg[v*2+1];
	}
	int query(int v, int L, int R, int QL, int QR){
		if (QL <= L && R <= QR) return seg[v];
		if (QR < L || R < QL) return 0;
		return query(v*2, L, (L+R)/2, QL, QR) + query(v*2+1, (L+R)/2+1, R, QL, QR);
	}
} seg;

int  n, a[200010], to[200010], from[200010], vcnt = 0;
lint dep[200010], rad;
vector<pair<int,lint>> graph[200010];

void dfs(int v, lint d){
	dep[v] = d; to[v] = ++vcnt;
	for (auto e : graph[v]){
		dfs(e.first, d + e.second);
	}
	from[v] = vcnt;
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
	seg.reset();
	vector<Event> es;
	for (int v=1; v<=n; ++v){
		es.push_back(Event(dep[v], 3, v));
		es.push_back(Event(dep[v], 1, v));
		es.push_back(Event(dep[v] - rad - 1, 2, v));
	}
	sort(es.begin(), es.end());
	for (auto &e : es){
		if (e.typ == 1 || e.typ == 2){
			seg.flip(1, 1, n, to[e.v]);
		}
		else{
			a[e.v] = seg.query(1, 1, n, to[e.v], from[e.v]);
		}
	}
	for (int i=1; i<=n; ++i){
		cout << a[i] << '\n';
	}
	return 0;
}