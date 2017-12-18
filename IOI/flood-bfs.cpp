#include <bits/stdc++.h>

using namespace std;

int n, nedge, X[100010], Y[100010];
int nxt[100010][4]; //0 is left, 1 is up, 2 is right, 3 is down
int fig[100010][4];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> X[i] >> Y[i];
	}
	cin >> nedge;
	for (int qq=0; qq<nedge; ++qq){
		int v, u; cin >> v >> u;
		if (X[v] == X[u]){ //vertical wall
			if (Y[v] > Y[u]) swap(v, u);
			nxt[v][1] = u;
			nxt[u][3] = v;
		}
		else if (Y[v] == Y[u]){ //horizontal wall
			if (X[v] > X[u]) swap(v, u);
			nxt[v][2] = u;
			nxt[u][0] = v;
		}
	}
	int curfig = 0;
	for (int st=1; st<=n; ++st){
		for (int i=0; i<4; ++i){
			if (nxt[st][i] != 0 && fig[st][i] == 0){
				++curfig;

				int dir = i;
				int v = st;

				while (fig[v][dir] == 0){
					fig[v][dir] = curfig;
					v = nxt[v][dir];
					dir = (dir + 3)%4;
					while (nxt[v][dir] == 0){
						dir = (dir + 3)%4;
					}
				}
			}
		}
	}

	return 0;
}