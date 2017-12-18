#include <bits/stdc++.h>

using namespace std;

long long P, N, V, R;
long long coeff[11], planets[100010][2];
bool danger[100010];

long long calc(long long x){
	long long ans = 0;

	for (long long i = 0; i < N; ++i){
		ans += coeff[i];

		ans *= x;
	}
	return ans;
}

long double dist(long long x1, long long y1, long long x2, long long y2){

	long double enddist = sqrt((long double)(x2 - x1)*(x2 - x1) + (long double)(y2 - y1)*(y2 - y1));
	return enddist;
}

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> P >> N >> V >> R;

	for (long long i=0; i<P; ++i){
		cin >> planets[i][0] >> planets[i][1];
	}
	for (long long i=0; i<N; ++i){
		cin >> coeff[i];
	}
	long long x_pos = V, y_pos = calc(V);
	long long ndanger = 0;
	for (long long i=0; i<P; ++i){
		if (planets[i][0] <= V && calc(planets[i][0]) == planets[i][1]){
			ndanger++;
		}
		else if (dist(x_pos, y_pos, planets[i][0], planets[i][1]) <= R){
			ndanger++;
		}
	}

	cout << ndanger;

	return 0;
}