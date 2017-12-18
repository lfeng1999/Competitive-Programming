#include <bits/stdc++.h>

using namespace std;

int main(){
	int y = 0, z = 100;
	int &x = y;
	x = z;
	x = 123;
	cout << x << " " << z << " " << y << endl;

}