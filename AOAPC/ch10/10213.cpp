#include <bits/stdc++.h>

using namespace std;

typedef long long ll;



int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int qq=0; qq<t; ++qq){
		long long N; cin >> N; N--;
		cout << 1 + (N*N*N*N - 2*N*N*N + 11*N*N + 14*N)/24 << endl;
	}
	return 0;
}