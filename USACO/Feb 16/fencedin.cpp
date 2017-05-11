#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

lint A, B, n, m;
vector<int> xs, ys;


int main(){
	// freopen("test.txt","r",stdin);
	freopen("fencedin.in","r",stdin);
	freopen("fencedin.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> A >> B >> n >> m;
	for (int i=0; i<n; ++i){
		int x; cin >> x;
		xs.push_back(x);
	}
	xs.push_back(A);
	for (int i=0; i<m; ++i){
		int y; cin >> y;
		ys.push_back(y);
	}
	ys.push_back(B);

	sort(ys.begin(), ys.end());
	sort(xs.begin(), xs.end());
	for (int i=ys.size()-1; i>0; --i){
		ys[i] -= ys[i-1];
	}
	for (int i=xs.size()-1; i>0; --i){
		xs[i] -= xs[i-1];
	}

	sort(xs.begin(), xs.end()); sort(ys.begin(), ys.end());
	reverse(ys.begin(), ys.end()); reverse(xs.begin(), xs.end());
	int up = m, rig = n; //check
	lint ans = 0;
	ans += xs.back()*m; xs.pop_back();
	ans += ys.back()*n; ys.pop_back();
	while (up != 0 && rig != 0){
		if (xs.back() <= ys.back()){
			ans += xs.back()*up; xs.pop_back();
			--rig; 
		}
		else{
			ans += ys.back()*rig; ys.pop_back();
			--up;
		}
	}
	cout << ans;
	return 0;
}