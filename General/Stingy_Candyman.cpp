#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int GCD(int a, int b)
{
	//cout << a << " " << b << endl;
	if (b == 0)
		return a;
	else
		return GCD(b, a%b);
}

int pow(int n, int k)
{
	int sum = 1;
	for (int i = 0; i < k; ++i)
		sum *= n;
	return sum;
}

int cbase(int base, int num)
{
	int total = 0;
	for (int i = 0; num != 0; ++i)
	{
		if (num % 10 >= base)
			return 0;
		total += (num%10)*pow(base, i);
		num /= 10;
	}
	return total;
}

int N = 0;
int vals[10][11];

void dfs(int n, vector<pair<int,int>> used) //term number, pair of new num and its original base
{
	//cout << n << endl;
	if (used.size() == N)
	{
		for (int i = 0; i != N; ++i)
			cout << used[i].second << endl;
		exit(0);
	}
	for (int i = 10; i >= 2; --i)
	{
		bool valid = true;
		if (vals[n][i] == 0)
			return;
		for (int j = 0; j != n; ++j)
		{
			if (GCD(max(used[j].first, vals[n][i]), min(used[j].first, vals[n][i])) != 1)
			{
				valid = false;
			}
		}
		//cout << valid;
		if (valid)
		{
			used.push_back(make_pair(vals[n][i], i));
			dfs(n + 1, used);
			used.pop_back();
		}
	}
}


int main()
{
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> vals[i][10];
		for (int j = 2; j <= 9; ++j)
			vals[i][j] = cbase(j, vals[i][10]);
	}
	for (int i = 2; i <= 10; ++i)
	{		
		vector<pair<int, int>> used;
		used.push_back(make_pair(vals[0][i], i));
		dfs(1, used);

	}
	//cout << GCD(9, 7) << endl << endl;
	//cout << vals[0][6] << " " << vals[1][8] << " " << vals[2][3] << endl;
	return 0;
}
