//http://codeforces.com/blog/entry/43499
//https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B
#include <bits/stdc++.h>

using namespace std;

typedef complex<double> Complex;

Complex fft(vector<Complex> cur){
	int N = cur.size();
	vector<Complex> even(N/2, Complex(0, 0)), odd(N/2, Complex(0, 0));
	for (int i=0; i<N; ++i){

	}
}



int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	return 0;
}