#include <bits/stdc++.h>

using namespace std;

int n, ucost, dcost, src;
int ans[500010];
set<int> up, down;
map<int,int> finans;
vector<pair<int,pair<int,int>>> fairs;

void do_update(int j){
	auto it = fairs[j];
	int t = it.first, l = it.second.first, m = it.second.second;
	int nxt;
	if (up.upper_bound(l) != up.begin()){
		nxt = *(--up.upper_bound(l));
		ans[l] = max(ans[l], ans[nxt] - (l - nxt)*dcost + m);
	}
	if (down.upper_bound(l) != down.end()){
		nxt = *down.upper_bound(l);
		ans[l] = max(ans[l], ans[nxt] - (nxt - l)*ucost + m);
	}
	finans[l] = max(finans[l], ans[l]);
}
void fix_sets(int j, vector<int> &remup, vector<int> &addup, vector<int> &remdown, vector<int> &adddown){
	int l = fairs[j].second.first;
	auto tmpit = up.upper_bound(l);
	while (tmpit != up.end()){
		if (ans[l] - (*tmpit - l)*dcost >= ans[*tmpit]){
			remup.push_back(*tmpit);
			up.erase(tmpit);
		}
		else{
			break;
		}
		tmpit = up.upper_bound(l);
	}
	tmpit = up.upper_bound(l);
	if (tmpit == up.begin() ){
		up.insert(l);
		addup.push_back(l);
	}
	else{
		--tmpit;
		if (ans[l] > ans[*tmpit] - (l - *tmpit)*dcost){
			up.insert(l);
			addup.push_back(l);
		}
	}

	tmpit = down.upper_bound(l);
	while (tmpit != down.begin()){
		--tmpit;
		if (ans[l] - (l - *tmpit)*ucost >= ans[*tmpit]){
			remdown.push_back(*tmpit);
			down.erase(tmpit);
		}
		else{
			break;
		}
		tmpit = down.upper_bound(l);
	}
	tmpit = down.upper_bound(l);
	if (tmpit == down.end()){
		down.insert(l);
		adddown.push_back(l);
	}
	else{
		if (ans[*tmpit] - (*tmpit - l)*ucost <= ans[l]){
			down.insert(l);
			adddown.push_back(l);
		}		
	}
}

void resetsets(vector<int> &remup, vector<int> &addup, vector<int> &remdown, vector<int> &adddown){
	for (int x : remup){
		up.insert(x);
	}
	for (int x : addup){
		up.erase(x);
	}
	for (int x : remdown){
		down.insert(x);
	}
	for (int x : adddown){
		down.erase(x);
	}
	remup = vector<int>();
	addup = vector<int>();
	remdown = vector<int>();
	adddown = vector<int>();
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> ucost >> dcost >> src;
	for (int qq=0; qq<n; ++qq){
		int t, l, m;
		cin >> t >> l >> m;
		fairs.push_back({t,{l, m}});
	}
	fill(ans, ans + 500010, -1e9);
	ans[src] = 0;
	sort(fairs.begin(), fairs.end());
	up.insert(src); down.insert(src);
	for (int i=0; i<fairs.size(); ++i){ //be careful of top down
		int j = i;
		finans.clear();
		vector<int> remup, addup;
		vector<int> remdown, adddown;
		for (; j < fairs.size() && fairs[i].first == fairs[j].first; ++j){
			finans[fairs[j].second.first] = -1e9;
			do_update(j);
			fix_sets(j, remup, addup, remdown, adddown);
		}
		for (int k=i; k<j; ++k){
			ans[fairs[k].second.first] = -1e9;
		}
		resetsets(remup, addup, remdown, adddown);
		--j;
		int fj = j;
		for (; j >= i; --j){
			do_update(j);
			fix_sets(j, remup, addup, remdown, adddown);
		}
		resetsets(remup, addup, remdown, adddown);
		for (int k=i; k<=fj; ++k){
			ans[fairs[k].second.first] = finans[fairs[k].second.first];
			fix_sets(k, remup, addup, remdown, adddown);
		}
		i = fj;
	}
	int best = 0;
	for (int i=0; i<=500001; ++i){
		if (i < src){
			best = max(best, ans[i] - (src - i)*dcost);
		}
		else{
			best = max(best, ans[i] - (i - src)*ucost);
		}
	}
	cout << best;
	return 0;
}