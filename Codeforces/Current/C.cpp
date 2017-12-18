#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
set<ll> s1[100010], s2[100010];
ll n, m, beads[100010], bsize;
ll calc[350][350];

void setup_beads(){
	for (ll i=1; i<=n; ++i){
		s1[i].clear(); s2[i].clear();
	}
	//setup calc
	for (ll i=0; i<n; ++i){
		s1[beads[i]].insert(i);
		s2[beads[i]].insert(i);
	}
	//setup calc to do
	for (ll i=0; i<n; i += bsize){
		ll cur = 0;
		map<ll,ll> last;
		ll k = i;
		ll lg = i/bsize, rg = i/bsize;
		for (ll j=i+bsize; j<n; j += bsize){
			for (; k<j; ++k){
				if (last.count(beads[k])){
					cur += k - last[beads[k]];
				}
				last[beads[k]] = k;
			}
			calc[lg][rg] = cur;
			++rg;
		}
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (ll i=0; i<n; ++i){
		cin >> beads[i];
	}
	
//#####
	bsize = 320; 
	// cout << bsize <<endl;	

	// setup_beads();
	// m = 1;
	for (ll L=0; L<m; L += bsize){
		setup_beads();
		ll R = min(L + bsize, m);
		set<ll> tochk;
		for (ll qq=L; qq<R; ++qq){
			ll typ; cin >> typ;
			if (typ == 1){
				ll p, x; cin >> p >> x; --p;
				tochk.insert(x);
				tochk.insert(beads[p]);
				s2[beads[p]].erase(p);
				s2[x].insert(p);
				beads[p] = x;
			}
			else{
				ll l, r; cin >> l >> r; --l; --r;
				ll ans = 0;
				if (r - l <= 2*bsize){
					map<ll,ll> last;
					for (ll i=l; i<=r; ++i){
						if (last.count(beads[i])){
							ans += i - last[beads[i]];
						}
						last[beads[i]] = i;
					}
				}
				else{
					ans += calc[l/bsize + 1][r/bsize - 1];
					// cout << l << " " << r << endl;
					ll lg = l/bsize + 1, rg = r/bsize - 1;
					// cout << "CURRENT ANS: " << ans << endl;
					// cout << "RANGE DONE: " << (l/bsize + 1)*bsize << " TO " << (r/bsize -1)*bsize << endl;
					set<ll> lol;
					for (ll i=l; i<lg*bsize; ++i){
						lol.insert(beads[i]);
					}
					for (ll i=rg*bsize; i<=r; ++i){
						lol.insert(beads[i]);
					}
					for (ll x : tochk){
						lol.insert(x);
					}

					for (ll x : lol){
						auto siter1 = s1[x].lower_bound(min(rg*bsize, n)), siter2 = s1[x].lower_bound(lg*bsize);
						if (siter1 == siter2) continue;
						ans -= *(--siter1);
						ans += *(siter2);
					}
					for (ll x : lol){
						auto siter1 = s2[x].upper_bound(r), siter2 = s2[x].lower_bound(l);
						if (siter1 == siter2) continue;
						ans += *(--siter1);
						ans -= *(siter2);
					}


				}
				cout << ans << '\n';
			}
		}

	}
	return 0;
}