#include <bits/stdc++.h>

using namespace std;

vector<int> graph[5010];
int par[5010], N, S, Q[5010], idx = 1;
int ml[5010], f[5010], c[5010], subsz[5010];

int solve(int d){
	for (int i=1; i<=N; ++i){
		f[i] = -1;
		c[i] = 1e9;
		if (subsz[i] == 0){
			f[i] = c[i] = d + 1;
		}
	}
	d *= 2;
	int ret = 0;
	for (int i=1; i<=N-1; ++i){
		int v = Q[i], p = par[Q[i]];
		if (subsz[v] == 0){
			f[p] = max(f[p], 1 + f[v]);
			c[p] = min(c[p], 1 + c[v]);
		}
		else{
			if (f[v] > d){
				// cout << v << endl;
				ret++;
				c[p] = min(c[p], 1);
				f[p] = max(f[p], 1);
			}
			else if (subsz[v] == 1){
				c[p] = min(c[p], c[v] + 1);
				f[p] = max(f[p], c[v] + 1);
			}
			else if (f[v] + c[v] > d + 1){
				c[p] = min(c[p], f[v] + 1);
				f[p] = max(f[p], f[v] + 1);
			}
			else{
				c[p] = min(c[p], c[v] + 1);
				f[p] = max(f[p], c[v] + 1);
			}
		}
	}
	int v = Q[N];
	if (f[v] + c[v] > d + 1){
		// cout << v << endl;
		ret++;
	}
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0);

	cin >> N >> S;
	for (int i=0; i<N-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	if (N == S){
		cout << 0;
		return 0;
	}
	idx = N;
	for (int i=1; i<=N; ++i){
		if (graph[i].size() != 1){
			Q[N] = i;
			break;
		}
	}//Only case doesn't work when there is 1 node or there is 2

	for (int i = N; i>0; --i){
		int v = Q[i];

		for (int u : graph[v]){
			if (u == par[v])
				continue;
			Q[--idx] = u;
			par[u] = v;
			subsz[v]++;
		}
	}
	// for (int i=1; i<=N; ++i){
	// 	cout << Q[i] << endl;
	// }
	int L = 1, R = N/(2*S) + 1;

	while (L < R){
		int mid = (L+R)/2;
		if (solve(mid) <= S)
			R = mid;
		else
			L = mid+1;
	}
	cout << L;
	// cout << solve(2) << endl;

	return 0;
}