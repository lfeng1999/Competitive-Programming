#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double ldouble;

int n;
vector<pair<double, double>> vs;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		double x, y; cin >> x >> y;
		vs.push_back(make_pair(x, y));
	}
	vs.push_back(vs[0]);
	vs.push_back(vs[1]);
	double best = 1e18;
	for (int i=1; i<=n; ++i){
		double a = 0, b = 0, c = 0;
		if (vs[i+1].first != vs[i-1].first){
			a = 1;
			b = -(vs[i+1].second - vs[i-1].second)/(vs[i+1].first - vs[i-1].first);
			c = -(vs[i+1].second + b*vs[i+1].first);
		}
		else{
			a = 0;
			b = 1;
			c = -vs[i+1].first;
		}
		double dist = abs(a*vs[i].second + b*vs[i].first + c)/sqrt(a*a + b*b);
		best = min(best, dist/2);
	}
	printf("%.7f", best);
	return 0;
}