#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int,int>> cows[1010];
vector<pair<int,int>> allcows;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("cowrect.in","r",stdin);
	freopen("cowrect.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for (int qq=0; qq<n; ++qq){
		int r, c; char ch; cin >> r >> c >> ch;
		cows[c].push_back(make_pair(r, (ch == 'H'?1:0)));
		if (ch == 'H') allcows.push_back(make_pair(r, c));
	}
	for (int i=0; i<=1000; ++i) sort(cows[i].begin(), cows[i].end());

	int best = 0, bestp = 0;
	for (auto &begcow : allcows){
		int begc = begcow.second, curr = begcow.first;
		int topr = 0, botr = 1000, totcow = 0;
		priority_queue<int, vector<int>, greater<int>> top;
		priority_queue<int> bot;
		for (int endc = begc; endc <= 1000; ++endc){
			for (auto &curcow : cows[endc]){
				int r = curcow.first;
				if (curcow.second == 0){ //rem cows
					if (r <= curr) topr = max(topr, r+1);
					if (curr <= r) botr = min(botr, r-1);
				}
				else{ //add cow
					if (topr <= r && r <= botr){
						totcow++;
						if (r <= curr) top.push(r);
						if (r >= curr) bot.push(r);
					}
				}
			}
			while (!top.empty() && topr > top.top()){
				top.pop();
				totcow--;
			}
			while (!bot.empty() && botr < bot.top()){
				bot.pop();
				totcow--;
			}
			if (topr > botr) break;
			if (totcow > best){
				best = totcow;
				bestp = (bot.top() - top.top())*(endc - begc);
			}
			else if (totcow == best){
				bestp = min(bestp, (bot.top() - top.top())*(endc - begc));
			}
		}
	}
	cout << best << endl << bestp << endl;

	return 0;
}