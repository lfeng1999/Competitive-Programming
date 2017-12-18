#include <bits/stdc++.h>

using namespace std;

int main(){
	freopen("test.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	srand(time(NULL));
	int n = 100000, nq = 100000;
	cout << n << " " << nq << '\n';
	for (int i=0; i<n; ++i){
		cout << rand()%100000 << " ";
	}
	for (int i=0; i<nq; ++i){
		int x = rand()%100000;
		int y = rand()%2;
		if (y) cout << "I ";
		else cout << "R ";
		cout << x << '\n';
	}


	return 0;
}