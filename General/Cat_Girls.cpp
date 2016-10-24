#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

long long N = 0, W = 0;
long long p = 0, c = 0, frame = 0;
char type = 'a';
int size = 0;

long long pcute[500001], pframe[500001], mcute[500001], lmost[500001]; //prefix cute prefix frame max cute from the right,  

int main()
{
	//ifstream file("Neko.txt");
	scanf("%lld%lld", &N, &W);
	for (int i = 0; i != N; ++i)
	{
		cin >> type;
		if (type == 'D')
		{
			pcute[size] = 0;
			pframe[0] = 0;
			mcute[size] = 0;
			--size;
		}
		else
		{
			++size;
			scanf("%lld%lld", &p, &c);
			pframe[size] = pframe[size - 1] + p;
			pcute[size] = pcute[size - 1] + c;
			lmost[size] = lower_bound(pframe + lmost[size - 1], pframe + size + 1, pframe[size] - W) - pframe;
			if (mcute[size - 1] < pcute[size] - pcute[lmost[size]])
				mcute[size] = pcute[size] - pcute[lmost[size]];
			else
				mcute[size] = mcute[size - 1];

			cout << mcute[size] << endl;
		}
	}
	return 0;
}