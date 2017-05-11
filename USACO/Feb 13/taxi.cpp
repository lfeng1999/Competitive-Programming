#include <bits/stdc++.h>
//You add up the distances that the cows must travel. The question now becomes the min cost to 
//match the exits of points to entrances.
//we make point 0 is an exit and n is an entrance to make the 2 points consistent with the algorithm

//now how do we do this? We can do it greedily. Sort the entrances and exits then match them one by one
//Prove it youself that greedy works
using namespace std;

typedef long long lint;
typedef pair<lint,lint> pii;

int n, m;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("taxi.in","r",stdin);
	freopen("taxi.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	vector<int> to, from;
	//exit, entrance
	to.push_back(0);
	from.push_back(m);
	lint ans = 0;
	for (int qq=0; qq<n; ++qq){
		int l, r; cin >> l >> r;
		ans += abs(l - r); //length of the cow distance
		to.push_back(r); from.push_back(l);
	}
	sort(from.begin(), from.end()); sort(to.begin(), to.end());
	for (int i=0; i<to.size(); ++i){
		ans += abs(to[i] - from[i]);
	}
	cout << ans;

	return 0;
}