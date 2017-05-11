#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const int MOD = 2012;
int dp[1010];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("bbreeds.in","r",stdin);
	freopen("bbreeds.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	string S; cin >> S;
	map<pair<int,int>,int> dp;
	dp[{0, 0}] = 1;
	for (int i=0; i<S.length(); ++i){
		map<pair<int,int>,int> nxt;
		if (S[i] == '('){
			for (auto &it : dp){
				nxt[{it.first.first+1, it.first.second}] += it.second;
				nxt[{it.first.first+1, it.first.second}] %= 2012;
				nxt[{it.first.first, it.first.second+1}] += it.second;
				nxt[{it.first.first, it.first.second+1}] %= 2012;
			}
		}
		else{
			for (auto &it : dp){
				if (it.first.first >= 1){
					nxt[{it.first.first-1, it.first.second}] += it.second;
					nxt[{it.first.first-1, it.first.second}] %= 2012;
				}
				if (it.first.second >= 1){
					nxt[{it.first.first, it.first.second-1}] += it.second;
					nxt[{it.first.first, it.first.second-1}] %= 2012;
				}
			}
		}
		dp = nxt;
	}
	cout << dp[{0, 0}];
	return 0;
}