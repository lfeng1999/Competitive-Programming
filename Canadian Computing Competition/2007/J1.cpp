#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
	int num1, num2, num3;
	cin >> num1 >> num2 >> num3;
	cout << num1 + num2 + num3 - max(num1, max(num2, num3)) - min(num1, min(num2, num3));
	return 0;
}