#include <bits/stdc++.h>

using namespace std;

int main(){
	freopen("test.txt","w",stdout);
	srand(time(NULL));
	int n = 18;
	cout << n << endl;
	for (int qq=0; qq<n; ++qq){
		cout << rand()%10000 << " ";
	}
	cout << 1;

}