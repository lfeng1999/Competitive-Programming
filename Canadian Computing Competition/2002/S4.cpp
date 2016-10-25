#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

int dp[102];
int last[102];
string name[102];
int times[102];

int main()
{
	ifstream file("Bridge Crossing.txt");
	int M = 0, Q = 0;
	scanf("%d%d", &M,&Q);
	for (int i = 1; i <= Q; ++i)
	{
		cin >> name[i];
		scanf("%d", &times[i]);
	}
	dp[0] = 0;
	name[0] = "";
	times[0] = 0;
	last[0] = 0;
	for (int i = 1; i <= M; ++i)
	{
		dp[i] = max(dp[i-1],times[i]);
		last[i] = 0;
	}
	for (int i = M+1; i <= Q; ++i)
	{
		dp[i] = 10000000;
		int mtime = times[i];
		for (int j = i; j != i - M; --j)
		{
			mtime = max(mtime, times[j]);
			if (dp[i] > dp[j-1] + mtime)
			{
				dp[i] = dp[j-1] + mtime;
				last[i] = j-1;
			}
		}
	}
	cout << "Total Time: " << dp[Q] << endl;
	stack<string> order;
	int start = Q;
	while (start!=0)
	{
		string phrase="";
		for (int i = last[start]+1; i <= start; ++i)
			phrase += name[i] + " ";
		order.push(phrase);
		start = last[start];
	}
	while (!order.empty())
	{
		cout << order.top() << endl;
		order.pop();
	}

	return 0;
}