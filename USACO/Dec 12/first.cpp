#include <bits/stdc++.h>

using namespace std;

int n, trie[300010][26], tcnt = 0;
bool isleaf[300010], adj[26][26];
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

int low_cut[26], disc[26], vc = 0, fkcnt[26];
bool ripped = false, onstk[26];
stack<int> stk;

void tarjan(int v, int p){
	low_cut[v] = disc[v] = ++vc;
	stk.push(v);
	onstk[v] = true;
	for (int i=0; i<26; ++i){
		if (adj[v][i] && adj[i][v]) ripped = false;
		if (i == v || i == p || !adj[v][i]) continue;
		if (disc[i] == 0){
			tarjan(i, v);
			low_cut[v] = min(low_cut[v], low_cut[i]);
		}
		else if (onstk[i]){
			low_cut[v] = min(low_cut[v], disc[i]);
		}
	}
	if (low_cut[v] == disc[v]){
		while (stk.top() != v){
			ripped = false;
			onstk[stk.top()] = false;
			stk.pop();
		}
		stk.pop();
		onstk[v] = false;
	}
}
int wtf = 0;
bool valid(){
	memset(low_cut, 0, sizeof(low_cut));memset(disc, 0, sizeof(disc)); memset(onstk, false, sizeof(onstk)); 
	while (!stk.empty()) stk.pop();
	ripped = true;
	vc = 0;
	for (int i=0; i<26; ++i){
		if (disc[i] == 0){
			tarjan(i, -1);
		}
	}
	return ripped;
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