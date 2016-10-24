#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int count = 0;
	cin >> count;
	for (int i = 0; i != count; ++i)
	{
		int A = 0, B = 0, P = 0, fun = 0;
		double F = 0;
		int a = 11, b = 25, c = 20, d = 6;
		cin >> a >> b >> c >> d;
		A = a - d;
		a -= A;
		b -= A * 2;
		c -= A * 2;

		F = (double(c) * 2 - double(b)) / 6;
		//cout << "WUWUW" << (c * 2 - b) / 6 << endl;
		//cout << A << " " << F << endl;
		c -= F * 3;
		a -= F;
		//cout << a << " " << b << " " << c  << endl;
		B = c - a;
		P = a - B;
		if (A < 0 | B < 0 | P < 0 | F < 0 | F != floor(F))
			fun = 1;
		if (fun)
			cout << "FUNNY FARM" << endl;
		else
			cout << A << " " << B << " " << P << " " << F << endl;
	}
	return 0;
}