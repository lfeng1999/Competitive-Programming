#include <iostream>
#include <cmath>

using namespace std;

bool prime[31623];

bool NTM[5000001];

int main()
{
	cin.sync_with_stdio(false);cin.tie(0);
	int N = 0, M = 0;
	cin >> N >> M;
        fill(prime,prime+31623,true);
        fill(NTM,NTM+5000001,true);
	for (int i = 2; i != 31623; ++i)
	{
		if (prime[i]);
		{
			for (int j = 2; j != floor(31622 / i) + 1; ++j)
				prime[i*j] = false;
			for (int j = floor(N / i); j <= M / i; ++j)
			{
				if (j >= 2)
				if (i*j >= N)
					NTM[i*j - N] = false;
			}
		}
	}
	for (int i = 0; i != M-N+1; ++i)
	{
		if (N+i!=1)
		if (NTM[i])
			printf("%d\n",i+N);
	}
	return 0;
}