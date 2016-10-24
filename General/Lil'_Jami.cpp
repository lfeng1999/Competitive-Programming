#include <iostream>

using namespace std;

int sweep[100001];

int main()
{
	int n = 0, k = 0;
	cin >> n >> k;
	for (int i = 0; i != k; ++i)
	{
		int cup = 0;
		cin >> cup;
		sweep[cup] += 1;
	}
	for (int i = 1; i <= n; ++i)
		sweep[i] += sweep[i - 1];
	int Q = 0;
	cin >> Q;
	for (int i = 0; i != Q; ++i)
	{
		int a = 0, b = 0;
		cin >> a >> b;
		cout << sweep[b] - sweep[a - 1] << endl;
	}
	return 0;
}