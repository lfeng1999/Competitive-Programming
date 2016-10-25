#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct res
{
	string name;
	int from, to;
};

res resid[101];
bool occup[101];
vector<string> order;

int main()
{
	int N = 0;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> resid[i].name >> resid[i].from >> resid[i].to;
		occup[resid[i].from] = true;
	}
	occup[0] = true;
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			if (!occup[resid[j].to])
			{
				occup[resid[j].to] = true;
				occup[resid[j].from] = false;
				resid[j].to = 0;
				order.push_back(resid[j].name);
			}
		}
		if (order.size() == N)
			break;
	}
	if (order.size() != N)
		cout << "Impossible" << endl;
	else
	{
		for (int i = 0; i != order.size(); ++i)
		{
			cout << order[i] << endl;
		}
	}


	return 0;
}