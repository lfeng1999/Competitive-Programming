#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define mp make_pair
#define rint(a) scanf("%d",&a)
#define rchar(a) scanf(" %c",&a)
int S, R, C, state[52][52][52], mv[3] = { -1, 0, 1 }; //row, p1, p2
bool obs[52][52], Qend, passed[52][52][52];

bool valid(int row, int p1, int p2)
{
	if (p2 <= p1 | p1 < 1 | p2 < 1 | p1 > C | p2 > C | obs[row][p1] | obs[row][p2])
		return false;
	return true;
}

int add(int p1, int p2)
{
	if (abs(p1 - p2) == 1)
		return 1;
	return 0;
}

void bfs()
{
	queue<pair<int, pair<int,int>>> Q; //first,second
	for (int i = 1; i <= C; ++i)
	if (!obs[1][i])
	for (int j = i + 1; j <= C; ++j)
	{
		if (!obs[1][j])
		{
			state[1][i][j] = add(i, j);
			passed[1][i][j] = true;
			Q.push(mp(1, mp(i, j)));
		}
	}
	while (!Q.empty())
	{
		int row = Q.front().first, p1 = Q.front().second.first, p2 = Q.front().second.second; Q.pop();
		//cout << row << " " << p1 << " " << p2 << endl;
		if (row == R)
		{
			Qend = true;
			continue;
		}
		for (int i = 0; i != 3; ++i)
		for (int j = 0; j != 3; ++j)
		{
			int np1 = p1 + mv[i], np2 = p2 + mv[j];
			if (valid(row + 1, np1,np2) && state[row][p1][p2] + add(np1, np2) > state[row + 1][np1][np2])
			{
				state[row + 1][np1][np2] = state[row][p1][p2] + add(np1, np2);
				if (!passed[row + 1][np1][np2])
					Q.push(mp(row + 1, mp(np1, np2)));
				passed[row + 1][np1][np2] = true;
			}
			else if (valid(row + 1, np1, np2) && state[row][p1][p2] + add(np1, np2) == state[row + 1][np1][np2] && !passed[row + 1][np1][np2])
			{
				Q.push(mp(row + 1, mp(np1, np2)));
				passed[row + 1][np1][np2] = true;
			}
		}
	}
}

int main()
{
	//freopen("PleasantStroll.txt", "r", stdin);
	rint(S);
	for (int k = 0; k != S; ++k)
	{
		Qend = false;
		memset(obs, true, sizeof(obs));
		memset(state, 0, sizeof(state));
		memset(passed, false, sizeof(passed));
		rint(R);
		rint(C);
		for (int i = 1; i <= R; ++i)
		{
			for (int j = 1; j <= C; ++j)
			{
				char a;
				rchar(a);
				obs[i][j] = (a == '#');
			}
		}
		bfs();
		if (!Qend)
			cout << "Detour" << endl;
		else
		{
			int maxh = 0;
			for (int i = 1; i <= C; ++i)
			for (int j = i + 1; j <= C; ++j)
			{
				maxh = max(maxh, state[R][i][j]);
			}
			cout << maxh << endl;
		}
	}
	return 0;
}