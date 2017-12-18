#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll n, ncow[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (ll i=1; i<=n; ++i){
		cin >> ncow[i];
	}
	stack<pair<ll,ll>> stk; 
	for (ll i=n; i>=1; --i){
		ll tot = ncow[i], ncnt = 1;
		while (!stk.empty()){
			ll avg = stk.top().first, tmpncnt = tot + stk.top().second;

			ll curavg = (tot - 1)/ncnt + 1;
			if (curavg >= avg){
				tot += stk.top().first*stk.top().second;
				ncnt += stk.top().second;
				stk.pop();
			}
			else
				break;
		}
		if (tot % ncnt == 0){
			stk.push({tot/ncnt, ncnt});
		}
		else{
			stk.push({tot/ncnt + 1, tot%ncnt});
			stk.push({tot/ncnt, ncnt - (tot%ncnt)});
		}
	}
	ll ans = 0;
	while (!stk.empty()){
		ans += stk.top().first*stk.top().first*stk.top().second;
		stk.pop();
	}
	cout << ans;

	return 0;
}