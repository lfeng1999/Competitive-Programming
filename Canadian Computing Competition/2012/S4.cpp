#include <iostream>
#include <set>
#include <queue>

using namespace std;

int pow(int a, int b)
{
	int x = 1;
	for (int i = 0; i != b; ++i)
		x *=a;
	return x;
}
set<int> visited;
int N, n, target;


int bfs(int hash)
{
	queue<pair<int,int>> Q; // hash and moves
	Q.push(make_pair(hash,0));
	while (!Q.empty())
	{
		int moves = Q.front().second; hash = Q.front().first; Q.pop();
		if (hash == target)
			return moves;
		if (!visited.insert(hash).second)
			continue;
		int stacks[9];
		for (int i = 0; i != 9; ++i)
			stacks[i] = 0x7fffffff;
		int nhash = hash;
		for (int i = N; i >= 1; --i)
		{ 
			int pos = nhash / pow(8, i);
			stacks[pos] = min(stacks[pos], i);
			nhash = nhash % pow(8, i);
		}
		//cout << stacks[1] << "  " << stacks[2] << "  " << stacks[3] << endl;
		for (int i = 1; i <= N; ++i)
		{
			if (i != 1)
			{
				if (stacks[i] < stacks[i - 1])
				{
					Q.push(make_pair(hash - pow(8, stacks[i]), moves + 1));
				}
			}
			if (i != N)
			{
				if (stacks[i] < stacks[i + 1])
				{
					Q.push(make_pair(hash + pow(8, stacks[i]), moves + 1));
				}
			}
		}
	}

	return -1;
}

int main()
{
	cin >> N;
	while (N != 0)
	{
		visited.clear();
		int hash = 0;
		target = 0;
		for (int i = 1; i <= N; ++i)
		{
			cin >> n;
			hash += i*pow(8, n);
		}
		for (int i = 1; i <= N; ++i)
		{
			target += i*pow(8, i);
		}
		int a = bfs(hash);
		if (a >= 0)
			cout << a << endl;
		else
			cout << "IMPOSSIBLE" << endl;
		cin >> N;
	}
	return 0;
}