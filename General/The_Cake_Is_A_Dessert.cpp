#include <iostream>
#include <fstream>

using namespace std;

long long cake[5001][5001];
int main()
{
	int N = 0, M = 0, K = 0, xe1 = 0, cy1 = 0, x2 = 0, cy2 = 0, Q = 0, a1 = 0, b1 = 0, a2 = 0, b2 = 0;
	//cin.sync_with_stdio(false);
	//cout.sync_with_stdio(false);
	//ifstream file("CakeisDessert.txt");
	scanf("%i%i%i", &N, &M, &K);
	for (int i = 0; i != K; ++i)
	{
		scanf("%i%i%i%i", &xe1, &cy1, &x2,&cy2);
		cake[cy1][xe1]++;
		cake[cy1][x2 + 1]--;
		cake[cy2 + 1][xe1]--;
		cake[cy2 + 1][x2+1]++;
	}
	for (int k = 0; k != 2; ++k)
	for (int i = 1; i <=N; ++i)
	{
		for (int j = 1; j <=M; ++j)
		{
			cake[j][i] += cake[j-1][i] + cake[j][i-1] - cake[j-1][i-1];
		}
	}
	scanf("%i", &Q);
	for (int i = 0; i != Q; ++i)
	{
		scanf("%i%i%i%i", &a1,&b1,&a2,&b2);
		printf("%lli\n",cake[b2][a2] - cake[b2][a1 - 1] - cake[b1 - 1][a2] + cake[b1 - 1][a1 - 1]);
	}

	return 0;
}