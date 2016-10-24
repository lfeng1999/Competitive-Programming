#include <iostream>
#include <cmath>

using namespace std;

void pos(double n)
{
	int count = 0;
	n = abs(n);
	while (n/10 > 1)
	{
		n /= 10;
		++count;
	}
	printf("%.3f", n);
	if (count)
		printf(" x 10^%i", count);
	cout << endl;
}

void rpos(double n)
{
	int count = 0;
	n = abs(n);
	while (n * 10 < 10)
	{
		n *= 10;
		++count;
	}
	printf("%.3f", n);
	printf(" x 10^-%i", count);
	cout << endl;
	return;
}


int main()
{
	double num = 0;
	cin >> num;
	while (num!=0)
	{
		int sign = (num < 0) ? -1 : 1;
		if (sign==-1)
			cout << "-";
		if (abs(num) >= 1)
			pos(num);
		else
			rpos(num);
		cin >> num;
	}
	return 0;
}