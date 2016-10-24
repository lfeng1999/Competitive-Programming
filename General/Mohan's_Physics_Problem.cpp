#include <iostream>
#include <algorithm>

using namespace std;

long long exponent[65];
long double scien[65];
int mexp[65];

int main()
{
	long long n = 0, k = 0;
	cin >> n >> k;
	
	exponent[0] = k;

	int counter = 1;
	while (k / 2 >=1)
	{
		exponent[counter - 1] = k % 2;
		exponent[counter] = k / 2;
		k /= 2;
		++counter;
	}
	long double sciform = n;
	int sciexp = 0;
	while (sciform / 10 >= 1)
	{
		sciform /= 10;
		++sciexp;
	}
	scien[0] = sciform;
	mexp[0] = sciexp;
	int expon = 0;
	for (int i = 1; i < counter; ++i)
	{
		long double sciform2 = scien[i - 1] * scien[i - 1];
		int sciexp2 = mexp[i - 1] * 2;
		while (sciform2 / 10 >= 1)
		{
			sciform2 /= 10;
			++sciexp2;
		}
		scien[i] = sciform2;
		mexp[i] = sciexp2;
	}
	long double total = 1;
	int totexp = 0;
	for (int i = 0; i < counter; ++i)
	{
		if (exponent[i])
		{
			total *= scien[i];
			totexp += mexp[i];
		}
	}
	while (total / 10 >= 0.99)
	{
		total /= 10;
		++totexp;
	}
	printf("%.2Lf", total);
	cout << endl << totexp;
	return 0;
}