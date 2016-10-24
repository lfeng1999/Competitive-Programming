#include <iostream>

using namespace std;

const int MAXN = 1026;
int bit[MAXN][MAXN], mov, S, X, Y, A, L, B, R, T;

void update(int x, int y, int val)
{
	for (; x <= S; x += x&-x)
	{
		for (int yy = y; yy <= S; yy += yy&-yy)
		{
			bit[x][yy] += val;
		}
	}
}

int query(int x, int y)
{
	int tot = 0;
	for (; x > 0; x -= x&-x)
	{
		for (int yy = y; yy > 0; yy -= yy&-yy)
		{
			tot += bit[x][yy];
		}
	}
	return tot;
}

int main()
{
	//freopen("MobilePhones.txt", "r", stdin);
	scanf("%d%d", &mov, &S);
	S++;
	while (true)
	{
		scanf("%d", &mov);
		if (mov == 1)
		{
			scanf("%d%d%d", &X, &Y, &A);
			X++, Y++;
			update(X, Y, A);
		}
		else if (mov == 2)
		{
			scanf("%d%d%d%d", &L, &B, &R, &T);
			L++, B++, R++, T++;
			printf("%d\n", query(R, T) - query(L - 1, T) - query(R, B - 1) + query(L - 1, B - 1));
		}
		else if (mov == 3)
			break;
	}
	return 0;
}