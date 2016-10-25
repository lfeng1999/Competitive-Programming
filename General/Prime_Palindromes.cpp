#include <iostream>

using namespace std;

int num[10];

bool primes[1000000];

bool palindrome(int n)
{
	int num[10];
	int number = 0;
	int counter = 0;
	while (n > 0)
	{
		num[counter] = n % 10;
		n /= 10;
		++counter;
	}
	for (int i = 0; i != counter; ++i)
	{
		if (num[i] != num[counter - i-1])
			return 0;
	}
	return 1;
}
int primecount[1000000];

int main()
{
	for (int i = 2; i != 1000000; ++i)
		primes[i] = true;
	for (int i = 2; i != 1000; ++i)
	for (int j = i; j <= 1000000/i; ++j)
	if (primes[i*j] && primes[i])
		primes[i*j] = false;

	primecount[2] = 1;
	primecount[3] = 2;
	for (int i = 4; i != 1000000; ++i)
	if (primes[i])
		primecount[i] = primecount[i - 1] + palindrome(i);
	else
		primecount[i] = primecount[i - 1];
	for (int i = 0; i != 5; ++i)
	{
		int L = 0, U = 0;
		cin >> L >> U;
		cout << primecount[U] - primecount[L-1] << endl;
	}
	return 0;
}