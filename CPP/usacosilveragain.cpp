#include <bits/stdc++.h>

using namespace std;

int C,N, cur, cur2;
int main(){
	freopen("helpcross.in","r",stdin);
	freopen("helpcross.out","w",stdout);
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
	sort(intervals.begin(), intervals.end());
	priority_queue<int, vector<int>, greater<int>> Q;
	int c = 0, i = 0, ans = 0;

	for (int val : chicken){
		while (i < N && intervals[i].first <= val){
			Q.push(intervals[i].second);
			i++;
		}
		while (!Q.empty() && val > Q.top()){
			Q.pop();
		}
		if (!Q.empty()){
			Q.pop();
			ans++;
		}
	}
	cout << ans;

	return 0;
}
