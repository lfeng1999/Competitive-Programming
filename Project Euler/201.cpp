#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 295426;
int freq[2][51][MAX_N];

int main(){

	int t = 0;
	freq[1][0][0] = freq[0][0][0] = 1;
	for (int i=1; i<=100; ++i){
		
		for (int j=1; j <= 50 && j<=i; ++j){
			for (int sum=1; sum<MAX_N ; ++sum){

				freq[t][j][sum] = freq[t^1][j][sum];
				if (sum >= i*i)
					freq[t][j][sum] += freq[t^1][j - 1][sum - i*i];
			}
		}
		t = t^1;
	}

	t = t^1;
	int ans = 0;
	for (int i=100*100; i<MAX_N; ++i){
		if (freq[t][50][i] == 1){
			ans += i;
		}
	}
	cout << ans;

	return 0;
}