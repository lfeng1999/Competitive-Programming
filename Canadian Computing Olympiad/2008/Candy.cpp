#include <iostream>
#include <fstream>

using namespace std;

int candies[101][2];
bool run[101][401];
long long total = 0;

int main()
{
	//ifstream file("Candy.txt");
	int N = 0;
	scanf("%i", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%i%i", candies[i], candies[i]+1);
	}
	run[0][200] = true;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j != 401; ++j)
		{
			if (run[i - 1][j])
			{
				int p = i - 1;
				int parity = candies[p][0] % 2;
				if (parity)
					{
					for (int k = 1; k <= candies[p][0]; k += 2)
					{
						if (j + k*candies[p][1] <= 400)
							run[i][j + k*candies[p][1]] = true;
						if (j - k*candies[p][1] >= 0)
							run[i][j - k*candies[p][1]] = true;
					}
				}
				else
				{
					for (int k = 0; k <= candies[p][0]; k += 2)
					{
						if (j + k*candies[p][1] <= 400)
							run[i][j + k*candies[p][1]] = true;
						if (j - k*candies[p][1] >= 0)
							run[i][j - k*candies[p][1]] = true;
					}
				}
			}
		}
	}
	for (int i = 0; i != 200; ++i)
	{
		if (run[N][200 - i] | run[N][200 + i])
		{
			cout << i;
			break;
		}
	}
}