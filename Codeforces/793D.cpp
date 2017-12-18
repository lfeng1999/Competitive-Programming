#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct State{
	int beg, ed, cur, nvis;
	State(int _beg, int _ed, int _cur, int _nvis){
		beg = _beg, ed = _ed, cur = _cur, nvis = _nvis;
	}
	bool operator < (const State &a) const{
		return nvis < a.nvis;
	}
};

int dp[82][82][82][82], g[81][81], n, k;
bool vs[81];
//beg, ed, current, how many past
priority_queue<pair<int,State>, vector<pair<int,State>>, greater<pair<int,State>>> Q;


int main(){
	// freopen("test.txt","r",stdin);
	// freopen()
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<81; ++i) fill(g[i], g[i]+81, 1e9);
	for (int i=0; i<82; ++i) for (int j=0; j<82; ++j) for (int k=0; k<82; ++k) for (int l=0; l<82; ++l) dp[i][j][k][l] = 1e9;
	cin >> n >> k;
	int m; cin >> m;
	if(k == 1){
		cout << 0; return 0;
	}
	for (int i=0; i<m; ++i){
		int v, u, d; cin >> v >> u >> d;
		g[v][u] = min(g[v][u], d);
		vs[v] = vs[u] = true;
	}
	for (int i=1; i<=n; ++i){
		if (vs[i]){
			dp[0][81][i][1] = 0;
			Q.push(make_pair(0, State(0, 81, i, 1)));
		}
	}
	while (!Q.empty()){
		auto st = Q.top().second;
		int tim = Q.top().first; Q.pop();
		int beg = st.beg, ed = st.ed, cur = st.cur, nvis = st.nvis;
		if (tim > dp[beg][ed][cur][nvis]) continue;
		if (nvis == k){
			cout << tim;
			return 0;
		}
		for (int i=beg+1; i<=ed-1; ++i){
			if (i == cur || g[cur][i] == 1e9) continue;
			if (i < cur){
				if (dp[beg][cur][i][nvis+1] > tim + g[cur][i]){
					dp[beg][cur][i][nvis+1] = tim + g[cur][i];
					Q.push(make_pair(dp[beg][cur][i][nvis+1], State(beg, cur, i, nvis+1)));
				}
			}
			else{
				if (dp[cur][ed][i][nvis+1] > tim + g[cur][i]){
					dp[cur][ed][i][nvis+1] = tim + g[cur][i];
					Q.push(make_pair(dp[cur][ed][i][nvis+1], State(cur, ed, i, nvis+1)));
				}
			}
		}		
	}
	cout << -1;

	return 0;
}