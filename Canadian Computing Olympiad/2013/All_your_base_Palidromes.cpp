#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int X;

bool tobase(int n, int b)
{
	vector<int> dig;
	while (n)
	{
		dig.push_back(n%b);
		n /= b;
	}
	for (int i = 0; i != dig.size() / 2; ++i)
	if (dig[i] != dig[dig.size() - i - 1])
		return false;
	return true;
}

int main()
{
	cin >> X;
	int mbase = sqrt(X);
	for (int i = 2; i <= sqrt(1000000000) && X > i; ++i)
	if (tobase(X, i))
		cout << i << endl;
	if (X > sqrt(1000000000))
	{
		for (int i = X/sqrt(1000000000); i != 0; --i)
		{
			if (X%i == 0)
				cout << X / i - 1 << endl;
		}
	}
	return 0;
}