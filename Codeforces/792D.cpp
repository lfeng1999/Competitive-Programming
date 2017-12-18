#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint n; int q, nbits;
lint move_left(lint x){
	bitset<64> b = x;
	if (b.test(0)) return x;
	for (int i=1; i < nbits; ++i){
		if (b.test(i)){
			b[i] = 0;
			b[i-1] = 1;
			break;
		}
	}
	x = b.to_ullong();
	return x;
}
lint move_right(lint x){
	bitset<64> b = x;
	if (b.test(0)) return x;
	for (int i=1; i<nbits; ++i){
		if (b.test(i)){
			b[i-1] = 1;
			break;
		}
	}
	x = b.to_ullong();
	return x;
}
lint move_up(lint x){
	bitset<64> b = x;
	if (x == (n+1)/2) return x;
	for (int i=0; i<nbits; ++i){
		if (b.test(i)){
			b[i] = 0;
			b[i+1] = 1;
			break;
		}
	}
	x = b.to_ullong();
	return x;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	nbits = log2(n+1); 
	for (int qq=0; qq<q; ++qq){
		lint u; cin >> u;
		string S;
		cin >> S;
		for (int i=0; i<S.length(); ++i){
			if (S[i] == 'U')
				u = move_up(u);
			else if (S[i] == 'L')
				u = move_left(u);
			else if (S[i] == 'R')
				u = move_right(u);
		}
		cout << u << '\n';
	}
	return 0;
}