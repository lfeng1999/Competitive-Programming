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
#include <functional>
#include <map>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIPII;
#define INF 1 << 30
#define INF2 0x3f3f3f3f
#define INF3 0x7fffffff
#define mp make_pair
#define pb push_back
#define MOD 1000000007]
#define mset(a) memset(a,0,sizeof(a))
#define mset2(a) memset(a,INF2,sizeof(a))
#define rint(x) scanf("%d",&x)
#define rchar(x) scanf(" %c",&x)
#define rll(x) scanf("%lld",&x)
#define MAXN 102

char box[1010][1010];
int N;
map<char, char> vert;
map<char, char> hori;
map<char, char> diag;

int odd()
{
	int cn = 0;
	int mid = (N + 1) / 2;
	bool flag = true;
	for (int i = 1; i <= mid; ++i)
	for (int j = 1; j <= N; ++j)
	if (box[i][j] != vert[box[N - i + 1][j]] | box[N - i + 1][j] != vert[box[i][j]])
		flag = false;
	if (flag)
		++cn;
	flag = true;
	for (int i = 1; i <= N; ++i)
	for (int j = 1; j <= mid; ++j)
	if (box[i][j] != hori[box[i][N-j+1]] | box[i][N-j+1] != hori[box[i][j]])
		flag = false;
	if (flag)
		++cn;
	return cn;
}


int main()
{
	//ifstream file("MockCCCJ4.txt");
	rint(N);
	for (int i = 1; i <= N; ++i)
	for (int j = 1; j <= N; ++j)
		rchar(box[i][j]);
	vert['.'] = '.';
	vert['('] = '(';
	vert[')'] = ')';
	vert['O'] = 'O';
	vert['/'] = '\\';
	vert['\\'] = '/';

	hori['.'] = '.';
	hori['('] = ')';
	hori[')'] = '(';
	hori['O'] = 'O';
	hori['/'] = '\\';
	hori['\\'] = '/';

	diag['.'] = '.';
	diag['('] = 'Q';
	diag[')'] = 'Q';
	diag['O'] = 'O';
	diag['/'] = '/';
	diag['\\'] = '\\';
	int counter = 0;
	bool flag = true;
	for (int i = 1; i <= N; ++i)
	for (int j = i; j <= N; ++j)
		if (box[i][j] != diag[box[j][i]] | box[j][i] != diag[box[i][j]])
			flag = false;
	if (flag)
		++counter;
	flag = true;
	for (int i = 1; i <= N; ++i)
	for (int j = N; j >= i; --j)
	if (box[i][j] != diag[box[j][i]] | box[j][i] != diag[box[i][j]])
		flag = false;
	if (flag)
		++counter;
	flag = true;
	counter += odd();
	cout << counter;
	return 0;
}