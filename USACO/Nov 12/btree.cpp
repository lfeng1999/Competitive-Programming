#include <bits/stdc++.h>

using namespace std;

struct Edge{
	int v, u, id;
} edges[100010];
int n;
bool used[100010];
vector<int> graph[40010];
char label[40010];
int dp1[100010], dp2[100010];
int past1[40010], past2[40010];
vector<int> fix1, fix2;

int solve1(int id){ //Count (
	int &ret = dp1[id];
	if (ret >= -1) return ret;
	int v = edges[id].u;
	ret = label[v] == '('?1:-1;
	past1[v]++;
	if (past1[v] == 2) fix1.push_back(v);
	for (int x : graph[v]){
		auto e = edges[x];
		if ((e.id^1) == id) continue;
		ret = max(ret, (label[v] == '('?1:-1) + solve1(e.id));
	}
	return ret;
}

int solve2(int id){ //Count )
	int &ret = dp2[id];
	if (ret >= -1) return ret;
	int v = edges[id].u;
	ret = label[v] == ')'?1:-1;
	past2[v]++;
	if (past2[v] == 2) fix2.push_back(v);
	for (int x : graph[v]){
		auto e = edges[x];
		if ((e.id^1) == id) continue;
		ret = max(ret, (label[v] == ')'?1:-1) + solve2(e.id));
	}
	return ret;
}

void adjust(){
	while (!fix1.empty()){
		int v = fix1.back(); fix1.pop_back();
		int r = 0;
		int toadd = label[v] == '('?1:-1;
		for (int i=0; i<graph[v].size(); ++i){
			int id = graph[v][i];
			dp1[id^1] = max(r, dp1[id^1]);
			r = max(r, toadd + dp1[id]);
		}
		r = 0;
		for (int i=graph[v].size()-1; i>=0; --i){
			int id = graph[v][i];
			dp1[id^1] = max(r, dp1[id^1]);
			r = max(r, toadd + dp1[id]);
		}
	}
	while (!fix2.empty()){
		int v = fix2.back(); fix2.pop_back();
		int r = 0;
		int toadd = label[v] == ')'?1:-1;
		for (int i=0; i<graph[v].size(); ++i){
			int id = graph[v][i];
			dp2[id^1] = max(r, dp2[id^1]);
			r = max(r, toadd + dp2[id]);
		}
		r = 0;
		for (int i=graph[v].size()-1; i>=0; --i){
			int id = graph[v][i];
			dp2[id^1] = max(r, dp2[id^1]);
			r = max(r, toadd + dp2[id]);
		}
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("btree.in","r",stdin);
	freopen("btree.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(dp1, dp1 + 100010, -1e9); fill(dp2, dp2 + 100010, -1e9);
	cin >> n;
	int id = -1;
	for (int i=2; i<=n; ++i){
		int p; cin >> p;
		edges[++id] = {i, p, id};
		graph[i].push_back(id);
		edges[++id] = {p, i, id};
		graph[p].push_back(id);
	}
	for (int i=1; i<=n; ++i){
		cin >> label[i];
	}
	int ans = 0;
	for (int v=1; v<=n; ++v){
		for (int i : graph[v]){
			auto e = edges[i];
			ans = max(ans, min(solve1(e.id^1), solve2(e.id)));
			adjust();
		}
	}
	cout << ans;
	return 0;
}