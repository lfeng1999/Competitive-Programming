#include <iostream>
#include <algorithm>

using namespace std;

int blood[8], take[8], units = 0;

void give(int a, int b)
{
	int mb = min(blood[a], take[b]);
	blood[a] -= mb;
	take[b] -= mb;
	units += mb;
}

int main()
{
	for (int i = 0; i != 8; ++i)
		cin >> blood[i];
	for (int i = 0; i != 8; ++i)
		cin >> take[i];
	give(0, 0);
	give(1, 1);
	give(0, 1);
	give(2, 2);
	give(0, 2);
	give(3, 3);
	give(2, 3);
	give(1, 3);
	give(0, 3);
	give(4, 4);
	give(0, 4);
	give(5, 5);
	give(4, 5);
	give(1, 5);
	give(0, 5);
	give(6, 6);
	give(4, 6);
	give(2, 6);
	give(0, 6);
	give(0, 7);
	give(1, 7);
	give(2, 7);
	give(3, 7);
	give(4, 7);
	give(5, 7);
	give(6, 7);
	give(7, 7);
	cout << units;
	return 0;
}