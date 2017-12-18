#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

int main(){
	freopen("test.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	srand(time(NULL));
	int nr, nc; nr = rand()%20, nc = rand()%20;
	
	cout << n << endl;
	for (int i=0; i<n; ++i){
		cout << rand()%20 << " ";
	}
	cout << endl;
	for (int i=0; i<n-1; ++i){
		cout << rand()%(i+1) << " " << rand()%2 << " ";
	}
	cout << endl;
	return 0;
}