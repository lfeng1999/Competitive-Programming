#include <iostream>

int F[10005];
int circ[10005];

using namespace std;

int main()
{
	int n = 6;
	cin >> n;
	for (int i = 0; i != n; ++i)
	{
		int k = 0;
		cin >> k;
		cin >> F[k];
	}
	int n1 = 1, n2 = 100, count=0,start=0;
	cin >> n1 >> n2;
	start = n1;
	while (n1 != 0 && n2 != 0)
	{
		while (true)
		{
			n1 = F[n1];
			++count;
			if (n1 == n2)
			{
				cout << "Yes" << " " << count - 1 << endl;
				break;
			}
			else if (n1 == start)
			{
				cout << "No" << endl;
				break;
			}
		}
		cin >> n1 >> n2;
		start = n1;
		count = 0;
	}



	return 0;
}