#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

long long B, phub[100010];
int RR, L, hub[100010];

bool valid(int L, int R)
{
	int mid = (L + R) / 2;
	if (phub[R] - phub[mid] * 2 + phub[L - 1] + (2 * mid - L + 1 - R)*hub[mid] <= B)
		return true;
	return false;
}

int main()
{
	//ifstream file("Ricehub.txt");
	scanf("%d%d%lld%d", &RR, &L, &B, &hub[0]);
	phub[0] = hub[0];
	for (int i = 1; i != RR; ++i)
	{
		scanf("%d", &hub[i]);
		phub[i] = phub[i - 1] + hub[i];
	}
	int L = 0, R = 0, chub = 0;
	while (R < RR)
	{
		while (R < RR && valid(L, R))
			R++;
		chub = max(chub, R - L);
		L++;
	}
	cout << chub;
	return 0;
}