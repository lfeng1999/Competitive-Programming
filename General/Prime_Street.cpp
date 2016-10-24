#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#define maxn 1300000

vector<long long> primes, comps; //prime, comp

long long psumL[100001], psumR[100001]; //prime, comp

bool prime[maxn];

void sieve()
{
	for (int i = 2; i != maxn; ++i)
	{
		if (prime[i])
		{
			for (int j = i * 2; j < maxn; j += i)
				prime[j] = false;
			primes.push_back(i);
		}
		else if (comps.size() < 100000)
			comps.push_back(i);
	}
}


int main()
{
	for (int i = 1; i < 1300000; i++)
		prime[i] = true;
	prime[1] = false;
	sieve();

	for (int i = 1; i <= 100000; ++i)
	{
		psumL[i] = psumL[i - 1] + primes[i - 1];
		psumR[i] = psumR[i - 1] + comps[i - 1];
	}

	long long N;
	int K;
	scanf("%lld%d", &N, &K);

	int minpos = 100000;
	long long minval = 10000000000;

	for (int i = 0; i <= 100000 - K; ++i)
	{
		long long Alex = psumL[i + K] - psumL[i] - N;
		long long Ben = psumR[i + K] - psumR[i];
		if (abs(Alex - Ben) < minval)
		{
			minval = abs(Alex - Ben);
			minpos = i + 1;
		}
	}
	cout << minpos;



	return 0;
}