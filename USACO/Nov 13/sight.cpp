#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358979;
int n, r;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("sight.in","r",stdin);
	freopen("sight.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	vector<pair<double,double>> lines;
	cin >> n >> r;
	for (int i=0; i<n; ++i){
		int x, y; cin >> x >> y;
		double cur = atan2(y, x);
		double alpha = acos((double)r/sqrt(1ll*x*x+1ll*y*y));
		if (cur-alpha < 0) cur += 2*PI;
		lines.push_back(make_pair(cur-alpha, cur+alpha));
	}
	sort(lines.begin(), lines.end());
	priority_queue<double, vector<double>, greater<double>> Q;
	int ans = 0;
	for (int qq=0; qq<2; ++qq){
		for (int i=0; i<n; ++i){
			while (!Q.empty() && Q.top() < lines[i].first){
				Q.pop();
			}
			if (qq) ans += Q.size();
			Q.push(lines[i].second);
			lines[i].first += 2*PI;
			lines[i].second += 2*PI;
		}
	}
	cout << ans;

	return 0;
}