#include <bits/stdc++.h>

using namespace std;

int N, curpoint, lowcut[410], vis[410], tim = 0, st;
bool apoint[410], past[410], in_graph[410];
vector<int> graph[410];
long long poss = 1, req = 0;

bool apexist = false, is_valid = true;
int subgsize = 0;

void tarjan(int v, int p){
	past[v] = true;
	lowcut[v] = tim;
	vis[v] = ++tim;

	subgsize++;

	int children = 0;
	for (int u : graph[v]){
		if (u == p) continue;

		if (past[u]){
			lowcut[v] = min(lowcut[v], vis[u]);
			continue;
		}
		tarjan(u, v);
		children++;
		lowcut[v] = min(lowcut[v], lowcut[u]);
		if ((v == st && children >=2) || (v != st && lowcut[u] >= vis[v])){
			apoint[v] = true;

			apexist = true;
		}
	}
}

void solve(int v, int p){
	if (apoint[v]) {
		is_valid = false;
	}
	past[v] = true;
	subgsize++;
	for (int u : graph[v]){
		if (past[u]) continue;
		solve(u, p);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	while(cin >> N && 	N){
		for (int i=0; i<410; ++i)
			graph[i].clear();
		memset(past, false, sizeof(past));
		memset(apoint, false, sizeof(apoint));
		memset(in_graph, false, sizeof(in_graph));
		for (int qq=0; qq<N; ++qq){
			int v, u; cin >> v >> u;
			graph[v].push_back(u);
			graph[u].push_back(v);
			in_graph[v] = in_graph[u] = true;
		}
		long long ans = 1, nExits = 0;
		for (st=1; st<=400; ++st){
			if (!past[st] && in_graph[st]){
				tarjan(st, -1);
				if (!apexist){
					nExits++;
					ans *= subgsize;
				}
				apexist = false;
				subgsize = 0;
			}
		}
		for (st=1; st<=400; ++st){
			if (apoint[st]){
				memset(past, false, sizeof(past));
				past[st] = true;
				for (int v : graph[st]){
					if (past[v]) continue;
					solve(v, st);
					if (is_valid){
						ans *= subgsize;
						nExits++;
					}
					is_valid = true;
					subgsize = 0;
				}
			}
		}
		cout << nExits << " " << ans << '\n';
	}

	return 0;
}