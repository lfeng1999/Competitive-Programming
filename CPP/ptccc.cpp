#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int xx1, yy1, xx2, yy2;

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> xx1 >> yy1 >> xx2 >> yy2;
	if (yy2 < yy1){
		swap(yy2, yy1);
		swap(xx2, xx1);
	}
	double slope = double(yy2-yy1)/double(xx2-xx1);

	double L = 0, R = 1e9;
	double best = 0;
	double bestslope = yy2/xx2;

	double area = (xx2*-slope - yy2)*(xx2*-slope - yy2)/slope/2;

	double area2 = (xx2*-bestslope - yy2)*(xx2*-bestslope - yy2)/slope/2;
	cout << max(area, area2);

	return 0;
}