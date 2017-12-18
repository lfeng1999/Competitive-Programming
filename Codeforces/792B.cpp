#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> a, p;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	int cur = 0;
	for (int i=1; i<=n; ++i){
		p.push_back(i);
	}
	for (int i=1; i<=k; ++i){
		int x; cin >> x;
		cur = (cur + x)%n;
		cout << p[cur] << " ";
		p.erase(p.begin() + cur);
		n--;
	}
	return 0;
}