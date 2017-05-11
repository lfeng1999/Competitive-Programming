#include <bits/stdc++.h>
//You add up the distances that the cows must travel. The question now becomes the min cost to 
//match the exits of points to entrances.
//we take note of how many times an edge is being used. e.g.) how many times we're going through 10 -> 35 or 10 <- 35
//We consider 10 -> 35 if there are more exits to the left of 10 than there are entrances on the right of 35
//more exits to the right is 10 <- 35
//Note that 10 and 35 are either an entrance or an exit
//The # times u use the distance from 10 <-> 35 is at min the diff in exits on the left and the entrances on the right or
//diff in exits on the right and entrances on the left. Note these 2 values are equal

//note w/o carrying cow only 1 direction. if there's an edge that bessie goes through in both directions w/o carrying cow
//u can always optimize this and make it 1 direction.

using namespace std;

typedef long long lint;
typedef pair<lint,lint> pii;

lint n, m;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("taxi.in","r",stdin);
	freopen("taxi.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m; 
	map<lint,lint> es; //takes care of diff for u, otherwise u can do map<lint,lint> exits, entrances
	es[0]++; es[m]--;
	lint ans = 0;
	for (lint qq=0; qq<n; ++qq){
		lint l, r; cin >> l >> r;
		es[l]--; es[r]++;
		ans += abs(l - r); 
	}
	lint cur = es.begin()->first, cursum = es.begin()->second;
	for (auto it = ++es.begin(); it != es.end(); ++it){
		ans += (it->first - cur)*abs(cursum);
		cursum += it->second;
		cur = it->first;
	}
	cout << ans;

	return 0;
}