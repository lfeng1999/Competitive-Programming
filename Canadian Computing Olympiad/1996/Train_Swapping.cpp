#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	for (int qq = 0; qq<n; qq++)
	{

		int len, train[51], count = 0;
		scanf("%d", &len);

		for (int i = 0; i<len; i++)
		{
			cin >> train[i];
		}


		bool go = true;
		while (go)
		{
			go = false;
			for (int s = 0; s<len - 1; s++)
			{
				if (train[s]>train[s + 1])
				{
					count++;
					swap(train[s], train[s + 1]);
					go = true;
				}
			}
		}

		printf("Optimal train swapping takes %d swap(s).\n", count);
	}
}
