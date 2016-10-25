#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	int num1=55, num2=10,temp=0,maxdiv=1;
	cin >> num1 >> num2;
	for (int i = 1; i <= num1; i++)
	{
		if ((num1%i == 0) && (num2%i == 0))
		{
			maxdiv = i;
		}
	}
	num1 = num1 / maxdiv;
	num2 = num2 / maxdiv;
	int whole;
	whole = num1 / num2;
	if (whole == num1)
		cout << whole;
	else if (whole == 0)
		cout << num1 << "/" << num2;
	else
		cout << whole << " " << num1 - whole*num2 << "/" << num2;

	return 0;
}