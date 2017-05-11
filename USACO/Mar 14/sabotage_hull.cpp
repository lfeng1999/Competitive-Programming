#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef complex<lint> pnt;

int n, cows[100010], psum[100010];

lint cross(pnt a, pnt b){
	return imag(conj(a) * b);
}

lint cross(pnt &a, pnt &b, pnt &c){
	return cross(b - a, c - a);
}


int main(){
	// freopen("test.txt","r",stdin);
	freopen("sabotage.in","r",stdin);
	freopen("sabotage.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> cows[i];
		psum[i] = cows[i] + psum[i-1];
	}
	vector<pnt> hull;
	pnt cur; cur.imag(cows[n]); cur.real(1);
	hull.push_back(cur);
	double ans = 1e9;
	int hrem = 0;
	for (int i=n-2; i>=1; --i){
		pnt tmp(-i, -psum[i]);
		int L = -1, R = hull.size()-1;
		while ((R - L) > 1){ //some binary shit needs fixing
			int mid = (L+R)/2;
			if (cross(tmp, hull[mid], hull[mid+1]) <= 0) L = mid;
			else R = mid;
		}
		pnt slope = hull[R] - tmp;
		ans = min(ans, (double)slope.imag()/slope.real());

		cur += pnt(1, cows[i+1]);
		//do some convex hull shit
		while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], cur) <= 0){ //I want the curve to look like sqrt(x) curve... 
			// cross(hull[hull.size()-2], hull[hull.size()-1], cur) > 0 gives a curve like x^2
			hull.pop_back();
		}
		hull.push_back(cur);
	}
	printf("%.3f", ans);
	return 0;
}