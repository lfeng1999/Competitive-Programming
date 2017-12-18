#include <bits/stdc++.h>

using namespace std;

ofstream mf;
ifstream of;

bool msort(const pair<int,int> a, const pair<int,int> b){
	return make_pair(a.second, b.first) < make_pair(b.second, a.first);
}

int C,N, cur, cur2;
int main(){
    mf.open("helpcross.out");
	of.open("helpcross.in");
	// freopen("test.txt","r",stdin);
	vector<int> chicken;
	vector<pair<int,int>> intervals;
	cin >> C >> N;
	for(int i = 0; i < C; i++){
	    cin >> cur;
        chicken.push_back(cur);
	}
    sort(chicken.begin(), chicken.end());
	for(int i = 0; i < N; i++){
        cin >> cur >> cur2;
        pair<int,int> meow = {cur,cur2};
        intervals.push_back(meow);
	}
	sort(intervals.begin(),intervals.end(), msort);

	int c = 0, i = 0, ans = 0;
	while (c < chicken.size() && i < intervals.size()){
		int L = intervals[i].first, R = intervals[i].second;
		int val = chicken[c];
		if (L <= val && val<= R){
			ans++;
			c++;
			i++;
			continue;
		}
		if (R < val){
			i++;
		}
		if (val < L){
			c++;
		}
	}
	cout << ans;

	return 0;
}
