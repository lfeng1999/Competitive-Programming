#include <iostream>

using namespace std;

int main()
{
	int t1 = 0, t2 = 0, len=2,t3=0;
	cin >> t1 >> t2;
	while (t1 >= t2)
	{
		t3 = t2;
		t2 = t1 - t2;
		t1 = t3;
		++len;
	}
	cout << len;
	return 0;
}