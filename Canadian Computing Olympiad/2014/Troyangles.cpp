#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2010;
int dp[MAXN][MAXN], N, tot = 0;

#define min3(a,b,c) min(min(a,b),c)
#define rint(a) scanf("%d",&a)
#define rchar(a) scanf(" %c",&a)

int main()
{
	//ifstream file("Troyangles.txt");
	//file >> N;
	rint(N);
	for (int i = 1; i <= N; ++i)
	for (int j = 1; j <= N; ++j)
	{
		char a;
		//file >> a;
		rchar(a);
		dp[i][j] = int(a == '#');
	}
	for (int i = N; i >= 1; --i)
		for (int j = N; j >= 1; --j)
		{
			if (dp[i][j]){
				dp[i][j] += min3(dp[i + 1][j + 1], dp[i + 1][j], dp[i + 1][j - 1]);
				tot += dp[i][j];
			}
		}
	cout << tot;
	return 0;
}