#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;

#define rint(a) scanf("%d",&a)
#define rchar(a) scanf(" %c", &a)
#define Fox(i, n) for (i = 0; i < n; ++i)
#define Fox1(i, n) for (i = 1; i <= n; ++i)
#define FoxI(i, a, b) for (i = a; i <= b; ++i)
#define Foxen(i, s) for (i = s.begin(); i!=s.end(); ++i)
#define max4(a,b,c,d) max(a,max(b,max(c,d)))
#define max3(a,b,c) max(a,max(b,c))
#define trace3(a,b,c) cout << a << " " << b << " " << c << endl

const int MAXN = 3010, MAXN2 = 105;

int p1[MAXN], p2[MAXN2], dp[MAXN][MAXN2][MAXN2], dp2[MAXN][MAXN2][MAXN2], N, M;

int dpbash2(int a, int b, int c);

int dpbash(int a, int b, int c)
{
	int& tot = dp[a][b][c];
	if (tot != -1)
	{
		return tot;
	}
	if (a == N)
	{
		if (c != b + 1)
			return tot = max(p2[c - 1] + dpbash2(a, b, c - 1), dpbash(a, b + 1, c));
		return tot = 0;
	}
	else if (b + 1 == c)
	{
		return tot = max(p1[a + 1] + dpbash2(a + 1, b, c), dpbash(a + 1, b, c));
	}
	return tot = max4(p1[a + 1] + dpbash2(a + 1, b, c), p2[c - 1] + dpbash2(a, b, c - 1), dpbash(a + 1, b, c), dpbash(a, b + 1, c));
}

int dpbash2(int a, int b, int c)
{
	int& tot = dp2[a][b][c];
	if (tot != -1)
		return tot;
	if (a == N)
	{
		if (c != b + 1)
			return tot = dpbash(a, b + 1, c);
		return tot = 0;
	}
	else if (b + 1 == c)
	{
		return tot = dpbash(a + 1, b, c);
	}
	return tot = max(dpbash(a + 1, b, c), dpbash(a,b+1,c));
}


int main()
{
	rint(N);
	for (int i = 1; i <= N; ++i)
		rint(p1[i]);
	rint(M);
	for (int j = 1; j <= M; ++j)
		rint(p2[j]);
	memset(dp, -1, sizeof(dp));
	memset(dp2, -1, sizeof(dp2));
	sort(p2, p2 + M + 1);
	printf("%d",dpbash(0, 0, M + 1));
	return 0;
}