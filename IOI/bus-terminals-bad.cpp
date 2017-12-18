#include <bits/stdc++.h>

using namespace std;

int n, X[510], Y[510];
int dist(int i, int j){
	return abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> X[i] >> Y[i];
	}
	int finans = 1e9;
	if (n == 1) finans = 0;
	for (int i=0; i<n; ++i){
		vector<int> ds;
		for (int j=0; j<n; ++j){
			if (i == j) continue;
			ds.push_back(dist(i, j));
		}
		sort(ds.begin(), ds.end(), greater<int>());
		if (i == 3){
			for (int x : ds){
				cout << x <<"  ";
			}
			cout << endl;
		}
		finans = min(finans, ds[0] + ds[1]);

	}
	cout << finans;
	return 0;
}