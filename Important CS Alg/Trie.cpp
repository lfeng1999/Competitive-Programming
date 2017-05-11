#include <bits/stdc++.h>

using namespace std;

const int MAXTRIE = 300010;
int nxt[MAXTRIE][26], t_cnt = 0, N, M;
vector<int> rng[MAXTRIE];
vector<int> ed[MAXTRIE];
string S;

void update(int v, int id, int cur){
	if (id == S.length()-1){
		ed[v].push_back(cur);
		return;
	}
	rng[v].push_back(cur);
	++id;
	if (nxt[v][S[id]-'a'] == -1){
		nxt[v][S[id]-'a'] = ++t_cnt;
	}
	update(nxt[v][S[id]-'a'], id, cur);
}

int query(int v, int id, int L, int R){
	if (v == -1) return 0;
	int ret = upper_bound(ed[v].begin(), ed[v].end(), R) - lower_bound(ed[v].begin(), ed[v].end(), L);
	if (id == S.length()-1){
		return ret + upper_bound(rng[v].begin(), rng[v].end(), R) - lower_bound(rng[v].begin(), rng[v].end(), L);
	}
	return ret + query(nxt[v][S[id+1]-'a'], id+1, L, R);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<MAXTRIE; ++i) for (int j=0; j<26; ++j) nxt[i][j] = -1; //default set trie
	cin >> N >> M;
	for (int i=1; i<=N; ++i){
		cin >> S;
		if (nxt[0][S[0]-'a'] == -1){
			nxt[0][S[0]-'a'] = ++t_cnt;
		}
		update(nxt[0][S[0]-'a'], 0, i);
	}
	for (int qq=0; qq<M; ++qq){
		cin >> S;
		int L, R; cin >> L >> R;
		cout << query(nxt[0][S[0]-'a'], 0, L, R) << '\n';
	}
	return 0;
}