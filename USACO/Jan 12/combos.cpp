#include <bits/stdc++.h>

using namespace std;

int trie[310][3], tcnt = 0, n, k, fail[310], val[310];
int dp[1010][310];

int solve(int i, int j){
	if (dp[i][j] != -1) return dp[i][j];
	if (i == k) return val[j];
	int &ret = dp[i][j];
	ret = val[j];
	for (int k=0; k<3; ++k){
		int p = j;
		while (p && !trie[p][k]){
			p = fail[p];
		}
		ret = max(ret, val[j] + solve(i+1, trie[p][k]));
	}
	return ret;
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<1010; ++i) for (int j=0; j<310; ++j) dp[i][j] = -1;
	cin >> n >> k;
	for (int i=0; i<n; ++i){
		string S; cin >> S;
		int p = 0;
		for (int j=0; j<S.length(); ++j){
			if (!trie[p][S[j]-'A']) 
				trie[p][S[j]-'A'] = ++tcnt;
			p = trie[p][S[j]-'A'];
		}
		val[p]++;
	}
	//now we need to connect the tries.
	queue<int> Q; Q.push(0);
	while (!Q.empty()){ //with a queue, we link the longest suffix to the longest prefix
		int p = Q.front(); Q.pop();
		// cout << p << endl;
		for (int i=0; i<3; ++i){ //'A', 'B', 'C'
			if (!trie[p][i]) continue;
			Q.push(trie[p][i]);
			if (p == 0){
				fail[trie[p][i]] = 0;
				continue;
			}
			int fp = fail[p];
			while (fp && !trie[fp][i]){
				fp = fail[fp];
			}
			fail[trie[p][i]] = trie[fp][i]; //linking the similar strings based on suffix to prefix
			val[trie[p][i]] += val[trie[fp][i]];
		}
	}
	cout << solve(0, 0);
	return 0;
}