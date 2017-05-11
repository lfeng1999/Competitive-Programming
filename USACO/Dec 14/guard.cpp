#include <bits/stdc++.h>

using namespace std;

struct Cow{
	int w, h, s;
	bool operator < (const Cow &a) const{
		return s < a.s;
	}
};

int n, H;
int height[1100010];
bool valid[1100010];

int main(){
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	vector<Cow> cows;
	cin >> n >> H;
	for (int i=0; i<n; ++i){
		int h, w, s; cin >> h >> w >> s;
		cows.push_back({w, h, s+w});
	}
	sort(cows.begin(), cows.end());
	int ans = -1e9;
	for (int mask = 1; mask < (1 << n); ++mask){
		bitset<21> b = mask;
		int msafe = 1e9, curweight = 0, curheight = 0;
		for (int i=0; i<n; ++i){
			if (b.test(i)){
				curweight += cows[i].w;
				curheight += cows[i].h;
				msafe = min(msafe, cows[i].s - curweight);
			}
		}
		if (curheight >= H){
			ans = max(ans, msafe);
		}
	}
	if (ans < 0){
		cout << "Mark is too tall";
	}
	else{
		cout << ans;
	}
	return 0;
}