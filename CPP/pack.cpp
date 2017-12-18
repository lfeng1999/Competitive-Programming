#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll dp[2000010], psum[2000010];
ll N, L;

ll dif(ll a, ll b){
	return abs(psum[b] + b - 1 - L - psum[a] - a);
}

ll C(ll a, ll b){
	return dp[a] + dif(a, b)*dif(a, b);
}
bool is_less(ll a, ll i, ll b){

	return (dp[a] - dp[b] + (dif(b, i) + dif(a, i)) - 1)/(dif(b, i) + dif(a, i)) <= (dif(b, i) - dif(a, i));
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> L;

	for (ll i=1; i<=N; ++i){
		cin >> psum[i];
		psum[i] += psum[i-1];
	}
	


	deque<pair<ll, pair<ll, ll>>> Q;
	Q.push_back(make_pair(0, make_pair(1, N))); //start node, begins range, ends range
	for (ll i=1; i<=N; ++i){
		if (i > Q.front().second.second)
			Q.pop_front();
		dp[i] = C(Q.front().first, i);
		while (!Q.empty() && C(i, Q.back().second.first) <= C(Q.back().first, Q.back().second.first)){
			Q.pop_back();
		}

		if (Q.empty()){
			Q.push_back(make_pair(i, make_pair(i+1, N)));
			continue;
		}

		ll L = Q.back().second.first, R = N;
			
		ll p = Q.back().first, beg = Q.back().second.first;
		while (L < R){
			ll mid = (L+R)/2 + 1;
			if ((N >= 1e5 && is_less(p, mid, i)) || (N <= 1e5 && C(p, mid) <= C(i, mid))){
				L = mid;
			}
			else{
				R = mid-1;
			}
		}
		Q.pop_back();
		Q.push_back(make_pair(p, make_pair(beg, L)));
		if (L != N)
			Q.push_back(make_pair(i, make_pair(L+1, N)));
	}
	cout << dp[N];




	return 0;
}