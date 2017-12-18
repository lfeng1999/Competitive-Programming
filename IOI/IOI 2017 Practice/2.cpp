#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef pair<int,int> pii;

int a, b;
int ask_shahrasb(int x, int y);

vector<int> find_cup(){
	int x = ask_shahrasb(0, 0);
	int tmp = ask_shahrasb(-(1 << 29), 0);
	bool posp = false, posq = false;
	if (tmp >= (1 << 29)){
		//then p is negative
		posp = true;
	}
	int tmp2 = ask_shahrasb(0, -(1 << 29));
	if (tmp2 >= (1 << 29)){
		//q is negative
		posq = true;
	}
	int p = 0, q = 0;
	bitset<32> b1 = x;
	// bool iszero = true;
	for (int i=0; i<29; ++i){
		int y;
		if (posp){
			y = ask_shahrasb(-(1 << i), 0);
		}
		else{
			y = ask_shahrasb((1 << i), 0);
		}
		// if (y != (1 << i)) iszero = false;
		bitset<32> b2 = y;
		for (int j=0; j<32; ++j){
			if (i == j) continue;
			if (b2.test(j) != b1.test(j)){
				p += (1 << i);
				break;
			}
		}
	}
	q = p^x;
	// cout << p << " " << q << endl;
	if (!posp) p *= -1;
	if (!posq) q *= -1;
	// if (posp && posq && iszero){
	// 	p = 0, q = 0;
	// }

	vector<int> ret(2, 0);
	ret[0] = p; ret[1] = q;
	return ret;
}

// int main(){
// 	freopen("test.txt","r",stdin);
// 	int T;
// 	cin >> T;
// 	// cout << ((-1)^(-2));
// 	for (int qq=0; qq<T; ++qq){
// 		cin >> a >> b;
// 		// cout << "CASE: " << qq + 1 << endl;
// 		// cout << a << " " << b << endl;
// 		// cout << (a^b) << endl;
// 		auto ans = find_cup();
// 		cout << ans[0] << " " << ans[1] << endl;
// 	}
// 	return 0;
// }