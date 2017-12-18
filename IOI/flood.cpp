#include <bits/stdc++.h>

using namespace std;

const int CLOCKWISE = 0, COUNTERCLOCKWISE = 1;
struct Edge{
	int v, u;
} es[400010];

int n, nedge;
int nxt[400010][2], X[100010], Y[100010], ptime[400010];
vector<int> used;
bool past[400010];
int curcnt = 0;

void walk(int cedge){
	while (!past[cedge]){
		used.push_back(cedge);
		past[cedge] = true;
		int v = es[cedge].v, u = es[cedge].u;
		int chk;
		if (nxt[u][0] == cedge){
			chk = 0;
		}
		else if (nxt[u][1] == cedge){
			chk = 1;
		}
		int dir;
		if (u%4 == 0){
			if (chk == 0){
				dir = CLOCKWISE;
			}
			else{
				dir = COUNTERCLOCKWISE;
			}
		}
		else if (u%4 == 1){
			if (chk == 0){
				dir = COUNTERCLOCKWISE;
			}
			else{
				dir = CLOCKWISE;
			}
		}
		else if (u%4 == 2){
			if (chk == 0){
				dir = CLOCKWISE;
			}
			else{
				dir = COUNTERCLOCKWISE;
			}

		}
		else if (u%4 == 3){
			if (chk == 0){
				dir = COUNTERCLOCKWISE;
			}
			else{
				dir = CLOCKWISE;
			}
		}


		chk ^= 1;
		int st = u%4;
		u /= 4;
		for (int qq=0; qq<4; ++qq){
			u = u*4 + st;
			if (nxt[u][chk] != 0){
				int to = nxt[u][chk];
				if (es[to].u == u) swap(es[to].u, es[to].v);
				cedge = to;
				break;
			}
			u /= 4;
			if (dir == CLOCKWISE)
				st = (st+1)%4;
			else
				st = (st+3)%4;
			chk ^= 1;
		}
	}
}
set<pair<int,int>> S;

int main(){//walk with hand against wall
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> X[i] >> Y[i];
	}
	cin >> nedge;
	int start = 0, leftmost = 1e9;
	for (int i=1; i<=nedge; ++i){
		int v, u;
		cin >> v >> u;
		if (X[v] == X[u]){ //vertical - 1
			if (Y[v] > Y[u]) swap(v, u);
			es[i*2] = {v*4+1, u*4+2}; //down - up
			es[i*2+1] = {v*4, u*4+3}; //down - up
			nxt[v*4+1][1] = nxt[u*4+2][1] = i*2;
			nxt[v*4][1] = nxt[u*4+3][1] = i*2+1;
		}
		else{ //horizontal - 0
			if (X[v] > X[u]) swap(v, u);

			S.insert(make_pair(Y[v], i*2));
			es[i*2] = {v*4+2, u*4+3}; //left - right
			es[i*2+1] = {v*4+1, u*4};
			nxt[v*4+2][0] = nxt[u*4+3][0] = i*2;
			nxt[v*4+1][0] = nxt[u*4][0] = i*2+1;
		}
	}
	while (!S.empty()){

		vector<int> Q;
		start = (*S.begin()).second;
		Q.push_back(start);

		while (!Q.empty()){
			for (int i=0; i<Q.size(); ++i){
				int v = Q[i];
				if (past[v]) continue;
				walk(v);
			}
			Q.clear();

			++curcnt;
			for (int x : used){
				if (x%2 == 0){
					S.erase(make_pair(Y[es[x].v/4], x));
				}
				ptime[x] = curcnt;
			}

			for (int x : used){
				if (!past[x^1]){
					Q.push_back(x^1);
				}
			}
			used.clear();
		}
	}

	int tot = 0;
	for (int i=2; i<=nedge*2; i += 2){
		if (ptime[i] == ptime[i^1]){
			tot++;
		}
	}
	cout << tot << '\n';
	for (int i=2; i<=nedge*2; i += 2){
		if (ptime[i] == ptime[i^1]){
			cout << i/2 << '\n';
		}
	}
	return 0;
}