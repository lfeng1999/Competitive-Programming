#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cout << '>' << #x << ":" x << endl
typedef long long lint;


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	if (n%2 == 0){
		cout << (n-2)/2;
	}
	else{
		cout << (n-1)/2;
	}
	return 0;
}