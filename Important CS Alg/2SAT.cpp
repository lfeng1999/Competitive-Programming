#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
const ll YES = 1, NO = 0;
vector<ll> graph[1000010];
ll N;
ll dp[1000010][2], occ[1000010];
bool fml[1000010], exists[1000010], past[1000010];

ll solve(ll v, ll p, ll take){ //take now
	ll &ret = dp[v][take];
	if (ret != -1) return ret;
	past[v] = true;
	ret = 1;
	ll yesmult = 1, nomult = 1, child = 0;
	for (ll u : graph[v]){
		if (u == p) continue;
		child++;
		nomult *= solve(u, v, NO);
		nomult %= MOD;
		yesmult *= solve(u, v, YES);
		yesmult %= MOD;
	}
	if (take == YES){ //can't take next ones
		ret *= nomult;
		ret %= MOD;
		ret *= (1 << occ[v]) - 1;
		ret %= MOD;
	}
	else if (child > 0) { //I have choices
		ret *= nomult + yesmult;
		ret %= MOD;
	}
	return ret;
}
ll a[1000010];
bool used[1000010];

ll gcd(ll a, ll b){
	if (b == 0) return a;
	return gcd(b, a%b);
}
int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (ll i=0; i<1000010; ++i) dp[i][0] = dp[i][1] = -1;
	cin >> N;
	for (ll i=0; i<N; ++i){
		ll x; cin >> a[i]; occ[a[i]]++;
		exists[a[i]] = true;
	}
	for (ll i=1; i<=500000; ++i){
		ll j = max((ll)1, (ll)sqrt(max((ll)0, i*i - 1000000)));
		if (i%2 == 1)
			j += j%2;
		else
			j += 1^(j%2);
		for (; j <= 500000/i && j < i; j+=2){
			if (gcd(max(i, j), min(i,j)) != 1) continue;
			if (exists[i*i - j*j] && exists[2*i*j]){
				// cout << i*i-j*j << " " << 2*i*j << endl;
				graph[i*i-j*j].push_back(2*i*j);
				graph[2*i*j].push_back(i*i-j*j);
			}
		}
	}
	// cout << 1 << endl;
	ll ans = 1;
	for (ll i=1; i<=1000000; ++i){
		if (exists[i] && !past[i]){
			// cout << i << endl;
			ans *= solve(i, -1, YES) + solve(i, -1, NO);
			ans %= MOD;
		}
	}
	cout << ans - 1;
	return 0;
}