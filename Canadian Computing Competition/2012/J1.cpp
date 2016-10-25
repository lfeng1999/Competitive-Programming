#include <iostream>

using namespace std;

int main()
{
	int lim = 0, speed = 0;
	cin >> lim >> speed;
	int x = speed - lim;
	if (x < 1)
		cout << "Congratulations, you are within the speed limit!";
	else if (1 <= x && x<= 20)
		cout << "You are speeding and your fine is $100.";
	else if (21 <= x && x<= 30)
		cout << "You are speeding and your fine is $270.";
	else
		cout << "You are speeding and your fine is $500.";
	return 0;
}