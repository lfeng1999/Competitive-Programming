#include <iostream>

int rate[201];
int slot[201];
int w[4001];
int c[4000];
int wa[4001];


using namespace std;

int main()
{
	int N = 2, M = 4, tot = 0;
	//rate[0] = 5, rate[1] = 2;
	//w[0] = 100, w[1] = 500, w[2] = 1000, w[3] = 2000;
	//c[0] = 3, c[1] = 1, c[2] = 2, c[3] = 4;
	//c[4] = -1, c[5] = -3, c[6] = -2, c[7] = -4;
	//rate[0] = 2, rate[1] = 3, rate[2] = 5;
	//w[0] = 200, w[1] = 100, w[2] = 300, w[3] = 800;
	//c[0] = 3, c[1] = 2, c[3] = 1, c[4] = 4;
	//c[2] = -3, c[5] = 4, c[6] = 2, c[7] = 1;
	cin >> N >> M;
	for (int i = 0; i != N; ++i)
		cin >> rate[i];
	for (int i = 0; i != M; ++i)
		cin >> w[i];
	int c1 = 0;
	for (int i = 0; i != 2 * M; ++i)
		cin >> c[i];

	int wcount = 0;
	int wcoun = 0;
	for (int k = 0; k != 2 * M; ++k)
	{
		if (c[k] < 0)
		{
			for (int j = 0; j != N; ++j)
			{
				if ((slot[j] +c[k])==0)
				{
					slot[j] = 0;
					if (wcoun < wcount)
					{
						slot[j] = wa[wcoun];
						tot += rate[j] * w[wa[wcoun] - 1];
						wcoun++;
					}
					break;
				}
			}
		}
		else
		{
			int pos = 1;
			for (int j = 0; j != N; ++j)
			{
				if (slot[j] == 0)
				{
					slot[j] = c[k];
					tot += rate[j] * w[c[k] - 1];
					pos = 0;
					break;
				}
			}
			if (pos)
			{
				wa[wcount] = c[k];
				wcount++;
			}
		}
	}
	cout << tot << endl;
	return 0;
}