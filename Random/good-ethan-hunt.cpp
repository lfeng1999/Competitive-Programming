#include <bits/stdc++.h>

using namespace std;

int nq;
int n;

vector<int> solve(int n){
	vector<int> ret;
	if (n == 0){
		ret.push_back(0);
		return ret;	
	}
	vector<int> lef = solve(n/2);
	vector<int> rig = solve((n-1)/2);
	for (int x : lef){
		ret.push_back(x*2);
	}
	for (int x : rig){
		ret.push_back(x*2+1);
	}
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nq;
	while (nq--){
		cin >> n;
		vector<int> ans = solve(n);
		for (int x : ans){
			cout << x << " ";
		}
		cout << '\n';
	}

	return 0;
}