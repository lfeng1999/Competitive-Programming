#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int GCD(int a, int b)
{
	if (b == 0)
		return a;
	else
		return GCD(b, a%b);
}

int LCM(int a, int b)
{
	return (a*b / GCD(a, b));
}


int main()
{
	//ifstream file("Dance.txt");
	int N = 0;
	cin >> N;
	while (N != 0)
	{
		int path[101];
		int past[101];
		for (int i = 0; i != 101; ++i)
		{
			path[i] = false;
			past[i] = false;
		}
		vector<int> length;
		for (int i = 0; i != N; ++i)
		{
			int c1 = 0, c2 = 0;
			cin >> c1 >> c2;
			path[c1] = c2;
		}
		for (int i = 1; i <= N; ++i)
		{
			if (!past[i])
			{
				int start = i;
				int counter = 0;
				while (!past[start])
				{
					++counter;
					past[start] = true;
					start = path[start];
				}
				length.push_back(counter);
			}
		}
		int lcm = length[0];
		for (int i = 1; i != length.size(); ++i)
		{
			lcm = LCM(lcm, length[i]);
		}
		cout << lcm << endl;

		cin >> N;
	}



	return 0;
}