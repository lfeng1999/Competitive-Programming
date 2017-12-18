#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef pair<int,int> pii;

int find_coin(vector<int> b){
	int x = 0;
	for (int i=0; i<64; ++i){
		if (b[i]) x ^= i;
	}
	return x;
}

vector<int> coin_flips(vector<int> b, int c){
	int x = 0;
	for (int i=0; i<64; ++i)
		if (b[i]) x ^= i;
	vector<int> ret;
	for (int i=0; i<64; ++i){
		if ((i ^ x) == c){
			ret.push_back(i);
			return ret;
		}
	}
	return ret;
}


// int main(){
// 	freopen("test.txt","r",stdin);
// 	cin.sync_with_stdio(0); cin.tie(0);
// 	int T;
// 	cin >> T;
// 	for (int qq=0; qq<T; ++qq){
// 		int c; cin >> c;
// 		vector<int> vec;
// 		for (int i=0; i<64; ++i){
// 			char ch; cin >> ch;
// 			vec.push_back(ch - '0');
// 		}
// 		cout << "CASE: " << qq + 1 << endl;
// 		auto ans = coin_flips(vec, c);
// 		int x = 0;
// 		// for (int i=0; i<64; ++i){
// 		// 	if (vec[i]) x  ^= i;
// 		// }
// 		// for (int i=0; i<64; ++i){
// 		// 	if (i ^ x)
// 		// }
// 		// cout << x << endl;
// 		// cout << ans[0] << endl;
// 		for (int x : ans)
// 			vec[x] ^= 1;
// 		cout << find_coin(vec) << endl;
// 	}
// 	return 0;
// }