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

vector<int> dd;
int N, ddf[100010];

int main()
{
	//ifstream file("MockCCCS2.txt");
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		int a = 0;
		cin >> a;
		dd.push_back(a);
	}
	sort(dd.begin(), dd.end());
	for (int i = 0; i != N; ++i)
	{
		//cout << dd[i] << " ";
		ddf[dd[i]] += 1;
	}
	int maxn = 0;
	for (int i = 100009; i >= 0; --i)
		maxn = max(ddf[i],maxn);
	cout << maxn;
	return 0;
}