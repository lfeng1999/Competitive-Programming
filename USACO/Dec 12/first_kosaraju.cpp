#include <bits/stdc++.h>

using namespace std;

int n, trie[300010][26], tcnt = 0;
bool isleaf[300010], adj[26][26], adj2[26][26];
string S;
void add(int v, int i){
	if (i == S.length()) {isleaf[v] = true; return;}
	if (trie[v][S[i]-'a'] == 0) trie[v][S[i]-'a'] = ++tcnt;
	add(trie[v][S[i]-'a'], i+1);
}

void solve(int v, int i){
	if (i != S.length() && isleaf[v]){
		adj[1][2] = adj[2][1] = 1; return;
	}
	else if (i == S.length()) return;
	vector<int> poss;
	for (int j=0; j<26; ++j) if (trie[v][j] != 0 && j != S[i] - 'a') adj[S[i]-'a'][j] = true;
	solve(trie[v][S[i]-'a'], i+1);
}

bool past[26];
stack<int> stk;

void dfs(int v){
	past[v] = true;
	for (int u=0; u<26; ++u)
		if (!past[u] && adj[v][u]) dfs(u);
	stk.push(v);
}
vector<int> cur;
void dfs2(int v){
	cur.push_back(v);
	past[v] = true;
	for (int u=0; u<26; ++u)
		if (!past[u] && adj2[v][u])
			dfs2(u);
}
bool valid(){
	memset(past, false, sizeof(past));
	memset(adj2, false, sizeof(adj2));
	bool ret = true;
	for (int i=0; i<26; ++i){
		if (!past[i]) dfs(i);
	}
	for (int i=0; i<26; ++i){
		for (int j=0; j<26; ++j){
			if (adj[i][j])
				adj2[j][i] = true;
		}
	}
	memset(past, false, sizeof(past));
	while (!stk.empty()){
		int v = stk.top(); stk.pop();
		if (past[v]) continue;
		dfs2(v);
		if (cur.size() >= 2) ret = false;
		cur.clear();
	}
	return ret;
}
 
vector<string> ss, ans;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("first.in","r",stdin);
	freopen("first.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> S; ss.push_back(S);
		add(0, 0);
	}
	for (int i=0; i<n; ++i){
		S = ss[i];
		solve(0, 0);
		if (valid()){
			ans.push_back(S);
		}
		memset(adj, false, sizeof(adj));
	}
	cout << ans.size() << '\n';
	for (auto &it : ans){
		cout << it << '\n';
	}
	return 0;
}