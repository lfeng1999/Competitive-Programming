#include <bits/stdc++.h>

using namespace std;
//Now Linear Solution

struct Update{
	int x, typ, i;
	bool operator < (const Update &a){
		if (x != a.x) return x < a.x;
		return typ > a.typ;
	}
};

int n, seq[1100010];
int nxtbig[1100010], nxtsmall[1100010];
unordered_map<int, stack<int>> M;
int lol[1100010];

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
	int ui = 0;
	vector<pair<int,int>> ans;
	for (int x=0; x<n; ++x){
		while (!M[seq[x] - x].empty() && nxtsmall[M[seq[x] - x].top()] <= x){
			M[seq[x] - x].pop();
		}
		if (!M[seq[x] - x].empty()){
			int nx = M[seq[x] - x].top();
			if (nx >= nxtbig[x]){
				if (lol[nx+1] == 0){
					lol[nx+1] = x + 1;
				}
			}
		}
		M[seq[x] - x].push(x);
	}
	vector<pair<int,int>> finans;
	for (int i=1; i<=n; ++i){
		if (lol[i]){
			while (!finans.empty() && finans.back().second >= lol[i]) finans.pop_back();
			finans.push_back({i, lol[i]});
		}
	}
	cout << finans.size() << '\n';
	for (auto it : finans){
		cout << it.first << " " << it.second << '\n';
	}

	return 0;
}