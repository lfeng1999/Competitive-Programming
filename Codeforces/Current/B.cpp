#include <bits/stdc++.h>

using namespace std;

int n, w, h;
map<int, vector<pair<int,int>>> xnodes, ynodes; //dif, x, and node #

pair<int,int> ans[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> w >> h;
	for (int qq=0; qq<n; ++qq){
		int typ, x, y; cin >> typ >> x >> y;
		if (typ == 1){
			xnodes[x - y].push_back({x, qq});
		}
		else{
			ynodes[x - y].push_back({x, qq});
		}
	}
	for (auto &it : xnodes){
		sort(it.second.begin(), it.second.end());
	}
	for (auto &it : ynodes){
		sort(it.second.begin(), it.second.end());
	}
	for (auto &it : xnodes){
		vector<int> eds;
		for (auto &it2 : it.second){
			eds.push_back(it2.first);
		}
		queue<int> Q;
		for (int i=it.second.size()-1; i >= 0; --i){
			Q.push(it.second[i].second);
		}
		for (auto &it2 : ynodes[it.first]){
			Q.pop();
			Q.push(it2.second);
		}
		while (!Q.empty()){
			ans[Q.front()] = make_pair(eds.back(), h);
			Q.pop();
			eds.pop_back();
		}
	}
	for (auto &it : ynodes){
		vector<int> eds;
		for (auto &it2 : it.second){
			eds.push_back(it2.first);
		}
		queue<int> Q;
		for (int i=it.second.size()-1; i >= 0; --i){
			Q.push(it.second[i].second);
		}
		for (auto &it2 : xnodes[it.first]){
			Q.pop();
			Q.push(it2.second);
		}
		while (!Q.empty()){
			ans[Q.front()] = make_pair(w, eds.back());
			Q.pop();
			eds.pop_back();
		}
	}


	for (int i=0; i<n; ++i){
		cout << ans[i].first << " " << ans[i].second << '\n';;
	}
	return 0;
}