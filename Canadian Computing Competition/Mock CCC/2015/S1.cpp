#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIPII;
#define INF 0x3f
#define INF2 0x7fffffff
#define mp make_pair
#define pb push_back
#define MOD 1000000007

int P, U, R1, R2;
set<PIPII> n;

bool check(int a, int b, int c)
{
	if (a + b + c == U && 2 * a + b - c == P)
	{
		n.insert(mp(a, mp(b, c)));
		//cout << a << " " << b << " " << c << endl;
		return true;
	}
	return false;
}

int main()
{
	//ifstream file("MockCCCs1.txt");
	cin >> P >> U >> R1 >> R2;

	int tot = R1 + R2, counter = 0;
	int mn = U / tot;
	for (int i = 1; i <= mn; ++i)
	{
		int R11 = i*R1, R22 = i*R2;
		counter += check(R11, R22, U - R11 - R22);
		counter += check(R22, U - R11 - R22, R11);
		counter += check(U - R11 - R22, R11, R22);
		counter += check(R11, U - R11 - R22, R22);
		counter += check(R22, R11, U - R11 - R22);
		counter += check(U - R11 - R22, R22, R11);
	}
	cout << n.size();

	return 0;
}