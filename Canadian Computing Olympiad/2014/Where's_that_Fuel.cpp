#include <iostream>

int pl[100001][2];

using namespace std;

int main()
{
	int N = 0, P = 0;
	int F = 0, cnt = 0, net = 1;
	cin >> N >> P;
	for (int i = 0; i != N; ++i)
	{
		int fuel = 0, cost = 0;
		cin >> fuel >> cost;
		if (i + 1 == P)
		{
			F = fuel;
		}
		else if (fuel >= cost)
		{
			pl[cnt][0] = fuel;
			pl[cnt][1] = cost;
			//cout << pl[cnt][0] << " " << pl[cnt][1] << endl;
			++cnt;
		}
	}
	//for (int i = 0; i != cnt; ++i)
	//{
		//cout << pl[i][0] << " " << pl[i][1] << endl;
	//}
	int count = 0;
	do
	{
		count = 0;
		for (int i = 0; i != cnt; ++i)
		{
			//cout << pl[i][0] << " " << pl[i][1] << " " << F << endl;
			if ((F >= pl[i][1]) && (pl[i][1] >= 0))
			{
				F = F - pl[i][1] + pl[i][0];
				count++;
				++net;
				pl[i][1] = -1;
			}
		}
	} while (count);

	cout << F << endl << net;
	return 0;
}