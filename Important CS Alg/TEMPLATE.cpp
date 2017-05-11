#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
typedef long long lint;
inline bool EQ(double a, double b) {return fabs(a-b) < 1e-9;}
inline int last_bit(int x){return x &(-x);}
inline int test(int x, int b){return (x >> b)&1;}
string fucker = "!#!@";

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	DEBUG(fucker);
	cout << last_bit(64) << endl;

	return 0;
}