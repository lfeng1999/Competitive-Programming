#include <bits/stdc++.h>

using namespace std;
long long inv(long long a, long long b){
	if (a == 1)
		return 1;
	cout << b - inv(b%a, a)*b/a << endl;
	return b - inv(b%a, a)*b/a;
}
int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cout << inv(5, 21)*5 << endl;
	return 0;
}