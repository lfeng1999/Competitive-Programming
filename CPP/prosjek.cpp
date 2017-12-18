#include <bits/stdc++.h>

using namespace std;

int N, K;
double arr[300010], temp[300010];

bool valid(double avg){
	for (int i=1; i<=N; ++i){
		temp[i] = arr[i] - avg;
	}
	double tot = 0, min_sub = 0, tot2 = 0;
	for (int i=1; i<=K; ++i){
		tot += temp[i];
	}
	for (int i=K+1; i<=N; ++i){
		tot += temp[i];
		tot2 += temp[i-K];
		min_sub = min(min_sub, tot2);
		if (tot - min_sub >= 0)
			return true;
	}
	return false;

}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N >> K;
	for (int i=1; i<=N; ++i){
		cin >> arr[i];
	}
	double L = 1, R = 1e6;
	int cnt = 0;
	while ((R - L) > 1e-8){
		double mid = (L+R)/2;
		if (valid(mid)){
			L = mid;
		}
		else{
			R = mid;
		}
	}
	printf("%.7f", L);

	return 0;
}