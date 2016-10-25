#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int N = 0, cmin=0;
	cin >> N;
	int fmax = sqrt(N) + 1;
	int i = 1;
	while (N != 1)
	{
		++i;
		if (N%i == 0)
		{
			cmin += i - 1;
			N = (N / i)*(i - 1);
			fmax = sqrt(N) + 1;
			i=1;
		}
		if (i == fmax)
		{
			cmin += N - 1;
			N -= 1;
			i = 1;
			fmax = sqrt(N) + 1;
		}
	}
	cout << cmin;

	return 0;
}