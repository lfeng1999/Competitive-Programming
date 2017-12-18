#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll modinv(ll a, ll b){
	if (a == 1) return 1;
	return b - modinv(b%a, a)*b/a;
}
ll gcd(ll a, ll b){
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a%b);
}

struct State{
	int a, b, t;
};
struct Cavemen{
	int c, p, t;
} cmen[16];

int n;
vector<State> states;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	int mincave = 1e9;
	for (int i=0; i<n; ++i){
		cin >> cmen[i].c >> cmen[i].p >> cmen[i].t;
		mincave = min(mincave, cmen[i].c);
		--cmen[i].c;
	}
	for (int i=0; i<n; ++i){
		for (int j=0; j<i; ++j){
			int mult;
			if (cmen[j].p - cmen[i].p >= 0) mult = 1;
			else mult = -1;
			states.push_back({mult*(cmen[i].c - cmen[j].c), mult*(cmen[j].p - cmen[i].p), min(cmen[i].t, cmen[j].t)});
			// print(states.back());
		}
	}
	// for (State x : states){
	// 	cout << x.a << " " << x.b << " " << x.t << endl;
	// }
	for (int i=mincave; i<=1000000; ++i){
		bool works = true;
		int mod = i;
		for (State cur : states){
			if (cur.b % mod == 0){
				if (abs(cur.a)%mod == 0){
					works = false;
					break;
				}
			}
			else{
				ll todiv = gcd(gcd(abs(cur.a), abs(cur.b)), mod);
				int na = cur.a / todiv, nb = cur.b / todiv;
				int nmod = mod / todiv;
				if (gcd(nb, nmod) != 1){
					continue;
				}
				na *= modinv(nb, nmod);
				int sign = na/abs(na);
				na = abs(na);
				int mult = na/nmod;
				na -= mult*nmod;
				na *= sign;
				na += nmod;
				na %= nmod;
				if (na <= cur.t){
					works = false;
					break;
				}
			}
		}
		if (works){
			cout << i << '\n';
			break;
		}
	}
	return 0;
}