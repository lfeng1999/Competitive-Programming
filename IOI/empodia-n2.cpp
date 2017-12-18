#include <bits/stdc++.h>

using namespace std;
//n^2 solution
struct Update{
	int x, typ, i;
	bool operator < (const Update &a){
		if (x != a.x) return x < a.x;
		return typ > a.typ;
	}
};

int n, seq[1100010];
int nxtbig[1100010], nxtsmall[1100010];
unordered_map<int, set<int>> M;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> seq[i];
		M[seq[i] - i];
	}
	stack<int> stk; stk.push(0);
	for (int i=1; i<n; ++i){
		while (!stk.empty() && seq[i] < seq[stk.top()]){
			nxtsmall[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()){
		nxtsmall[stk.top()] = n; //past lim
		stk.pop();
	}
	stk.push(n-1);
	for (int i=n-2; i>=0; --i){
		while (!stk.empty() && seq[i] > seq[stk.top()]){
			nxtbig[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()){
		nxtbig[stk.top()] = -1;
		stk.pop();
	}
	vector<Update> updates;
	for (int i=0; i<n; ++i){
		updates.push_back({nxtbig[i]+1, 1, i});
		updates.push_back({i, -1, i});
	}
	sort(updates.begin(), updates.end());
	int ui = 0;
	vector<pair<int,int>> ans;
	for (int x=0; x<n; ++x){
		while (ui < updates.size() && updates[ui].x <= x){
			int i = updates[ui].i;
			if (updates[ui].typ == -1){
				M[seq[i] - i].erase(i);
			}
			else{
				M[seq[i] - i].insert(i);
			}
			++ui;
		}

		if (!M[seq[x] - x].empty()){
			int nx = *M[seq[x] - x].begin();
			if (nx <= nxtsmall[x] - 1){
				ans.push_back({x, nx});
			}
		}
	}
	vector<pair<int,int>> finans;

	for (auto it : ans){
		while (!finans.empty() && finans.back().second >= it.second) finans.pop_back();
		finans.push_back(it);
	}
	cout << finans.size() << '\n';
	for (auto it : finans){
		cout << it.first + 1 << " " << it.second + 1 << '\n';
	}

	return 0;
}