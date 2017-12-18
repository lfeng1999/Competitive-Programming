#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> arr[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int qq=0; qq<n; ++qq){
		int a, b; cin >> a >> b;
		arr[a].push_back(b);
	}
	int nq;
	cin >> nq;
	for (int qq=0; qq<nq; ++qq){
		int m; cin >> m;
		vector<int> qs;
		for (int pp=0; pp<m; ++pp){
			int x; cin >> x;
			qs.push_back(x);
		}
		sort(qs.begin(), qs.end());
		priority_queue<int, vector<int>, greater<int>> Q;
		int j = 0;
		bool works = true;
		for (int x : qs){
			while (j <= x){
				for (int y : arr[j]){
					Q.push(y);
				}
				++j;
			}
			while (!Q.empty() && Q.top() < x) Q.pop();
			if (Q.size() < x){
				works = false;
				break;
			}
			for (int pp=0; pp<x; ++pp){
				Q.pop();
			}
		}
		cout << (works?1:0) << '\n';
	}
	return 0;
}