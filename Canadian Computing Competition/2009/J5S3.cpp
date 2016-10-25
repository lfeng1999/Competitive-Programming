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
#define INF2 0x3f
#define INF 0x7fffffff
#define mp make_pair
#define pb push_back

int x, y, d[51];
char m;
bool s[51][51], ff[51];


void cedge(int a, int b)
{
	s[a][b] = s[b][a] = true;
}
void dedge(int a, int b)
{
	s[a][b] = s[b][a] = false;
}

void spfa(int a, int b)
{
	memset(d, INF2, sizeof(d));
	queue<int> Q;
	Q.push(a);
	d[a] = 0;
	while (!Q.empty())
	{
		int top = Q.front(); Q.pop();
		for (int i = 0; i != 51; ++i)
		{
			if (s[top][i] && d[top] + 1 < d[i])
			{
				d[i] = d[top] + 1;
				Q.push(i);
			}
		}
	}
}

int main()
{
	cedge(2, 6);
	cedge(1, 6);
	cedge(7, 6);
	cedge(5, 6);
	cedge(4, 6);
	cedge(3, 6);
	cedge(3, 5);
	cedge(3, 4);
	cedge(5, 4);
	cedge(7, 8);
	cedge(9, 8);
	cedge(9, 10);
	cedge(9, 12);
	cedge(11, 10);
	cedge(11, 12);
	cedge(12, 13);
	cedge(15, 13);
	cedge(14, 13);
	cedge(15, 3);
	cedge(17, 16);
	cedge(17, 18);
	cedge(16, 18);
	//ifstream file("Seperation.txt");
	cin >> m;
	while (m != 'q')
	{
		if (m == 'i')
		{
			cin >> x >> y;
			cedge(x, y);
		}
		else if (m == 'n')
		{
			int fcount = 0;
			cin >> x;
			for (int i = 0; i != 51; ++i)
				fcount += s[x][i];
			cout << fcount << endl;
		}
		else if (m == 'f')
		{
			memset(ff, false, sizeof(ff));
			int fcount = 0;
			cin >> x;
			for (int i = 0; i != 51; ++i)
			{
				if (s[x][i])
				{
					for (int j = 0; j != 51; ++j)
					if (s[i][j])
						ff[j] = true;
				}
			}
			for (int i = 0; i != 51; ++i)
				if (s[x][i])
					ff[i] = false;
			ff[x] = false;
			for (int i = 0; i != 51; ++i)
				fcount += ff[i];
			cout << fcount << endl;
		}
		else if (m == 's')
		{
			cin >> x >> y;
			spfa(x, y);
			if (d[y] <= INF2)
				cout << d[y] << endl;
			else
				cout << "Not connected" << endl;
		}
		else if (m == 'd')
		{
			cin >> x >> y;
			dedge(x, y);
		}
		cin >> m;
	}
	return 0;
}