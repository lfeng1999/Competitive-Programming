#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int times[1001];
int timer[1001];
int wait[1001];

vector<int> wake[1001];

int D = 0, F = 0, T = 0;

void bark()
{
	for (int time = 0; time <= T; ++time)
	for (int i = 1; i <= D; ++i)
	{
		if (timer[i] == time)
		{
			times[i]++;
			for (int j = 0; j !=wake[i].size(); ++j)
			{
				if (timer[wake[i][j]] < time)
					timer[wake[i][j]] = time + wait[wake[i][j]];
				else
					timer[wake[i][j]] = min(timer[wake[i][j]], time + wait[wake[i][j]]);

			}
		}
	}
}

int main()
{
	for (int i = 0; i != 1001; ++i)
		timer[i] = -1;
	timer[1] = 0;
	scanf("%d", &D);

	for (int i = 1; i <= D; ++i)
		scanf("%d", &wait[i]);
	cin >> F;
	for (int i = 0; i != F; ++i)
	{
		int d1, d2;
		scanf("%d%d", &d1,&d2);
		wake[d1].push_back(d2);
	}
	cin >> T;
	bark();

	for (int i = 1; i <= D; ++i)
		cout << times[i] << endl;

	return 0;
}