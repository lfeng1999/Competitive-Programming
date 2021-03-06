#include <bits/stdc++.h>

using namespace std;

pair<int,int> extendedGCD(int a, int b){
//conditions: a, b are positive... a > b
	if (b == 0) return make_pair(1, 0); //special case if a is positive and b is 0
	if (a%(a%b) == b%(a%b) && a%(a%b) == 0) return make_pair(1, -a/b);

	pair<int,int> nxt = extendedGCD(b, a % b);
	pair<int,int> cur = make_pair(1, -a/b);
	return make_pair(cur.first*nxt.second, nxt.first + nxt.second*cur.second);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int x = 321*7*3*5, y = 3124*7*3*5;
	pair<int,int> lol = extendedGCD(y, x);
	cout << y*lol.first + x*lol.second << endl;
	return 0;
}