#include <bits/stdc++.h>

using namespace std;

bool past[1010];

int main(){
	cin.sync_with_stdio(0); cin.tie(0);

	for (int i=0; i<1000; i+=3){
		past[i] = true;
	}

	for (int i=0; i<1000; i+=5){
		past[i] = true;
	}
	int ans = 0;
	for (int i=0; i<=1000; ++i){
		if (past[i])
			ans += i;
	}
	cout << ans;
	return 0;
}