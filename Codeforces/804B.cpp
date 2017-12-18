#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cout << '>' << #x << ":" x << endl
typedef long long lint;
lint MOD = 1000000007;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	string s;
	cin >> s;
	lint ans = 0;
	lint nb = 0;
	for (int i=s.length()-1; i>=0; --i){
		if (s[i] == 'b'){
			nb++;
		}
		else{
			ans += nb;
			ans %= MOD;
			nb *= 2;
			nb %= MOD;
		}
	}
	cout << ans;
	return 0;
}