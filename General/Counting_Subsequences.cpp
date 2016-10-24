#include <iostream>
#include <map>
#include <string>

using namespace std;

long long dp[100001];
map<char, int> lpos;
string line;

int main()
{
	cin >> line;
	dp[0] = 1;
	lpos[line[0]] = 0;
	for (int i = 1; i != line.size(); ++i)
	{
		dp[i] = dp[i - 1] * 2 + 1; // with or without the last term add for if its an empty set
		if (lpos.count(line[i]))
		{
			if (lpos[line[i]])
				dp[i] -= dp[lpos[line[i]] - 1] + 1;
			else
				dp[i] -= 1;
		}
		lpos[line[i]] = i;
		dp[i] = (dp[i] + 10007) % 10007;
	}
	cout << dp[line.size() - 1];
	return 0;
}