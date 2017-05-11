#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint n, maxlen, bw[100010], bh[100010], dp[100010];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	deque<pair<lint,lint>> Q;
	cin >> n >> maxlen;
	multiset<lint> ans;
	lint len = 0;
	for (lint L=1, R = 1; R <= n; ++R){
		cin >> bh[R] >> bw[R];
		len += bw[R];
		while (len > maxlen && !Q.empty()){
			lint toerase = Q.front().first + dp[L-1];
			ans.erase(toerase);
			Q.front().second--;
			len -= bw[L];

			L++;
			if (Q.front().second == 0) Q.pop_front();
			else{
				lint toadd = Q.front().first + dp[L-1];
				ans.insert(toadd);
			}
		}
		pair<lint,lint> toadd = make_pair(bh[R], 1);
		while (!Q.empty() && Q.back().first <= toadd.first){
			toadd.second += Q.back().second;
			lint toerase = Q.back().first + dp[R-toadd.second];
			ans.erase(toerase);
			Q.pop_back();
		}
		Q.push_back(toadd);
		lint addval = toadd.first + dp[R - toadd.second];
		ans.insert(addval);
		dp[R] = *ans.begin();
	}
	cout << dp[n];
	return 0;
}