#include <iostream>
#include <algorithm>
#include <set>
int A[5400];
using namespace std;

int main()
{
	int c[32];
	int dis = 100, cnum = 3;
	cin >> dis >> cnum;
	for (int i = 0; i != cnum; ++i)
	{
		cin >> c[i];
	}
	for (int i = 0; i != 5400; ++i)
		A[i] = 10000;
	A[0] = 0;
	//c[0] = 33, c[1] = 66, c[2] = 1;
	for (int i = 0; i != dis+1; ++i)
	for (int j = 0; j != cnum; ++j)
	{
		A[i + c[j]] = min(A[i + c[j]], A[i] + 1);
		//cout << i + c[j] << " " << A[i + c[j]] << endl;
	}
	if (A[dis] == 10000)
		cout << "Roberta acknowledges defeat.";
	else
		cout << "Roberta wins in " << A[dis] << " strokes.";
	return 0;
}