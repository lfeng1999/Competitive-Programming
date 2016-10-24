#include <iostream>

using namespace std;


int GCD(int a, int b)
{
	if (b==0)
		return a;
	else
	{
		return GCD(b, a%b);
	}
}

int LCM(int a, int b)
{
	return a*b / GCD(a, b);
}


void sum(int n1, int d1, int n2, int d2)
{
	int lcm = LCM(d1, d2);
	n1 *= lcm / d1;
	n2 *= lcm / d2;
	int n3 = 0, d3 = 0;
	n3 = n1 + n2;
	d3 = lcm;
	int gcd = GCD(n3, d3);
	n3 /= gcd;
	d3 /= gcd;
	if (d3 != 1)
		cout << n3 << " " << d3 << endl;
	else
		cout << n3 << endl;
}

int main()
{
	for (int i = 0; i != 5; ++i)
	{
		int n1, d1, n2, d2;
		cin >> n1 >> d1 >> n2 >> d2;
		sum(n1, d1, n2, d2);
	}
	return 0;
}