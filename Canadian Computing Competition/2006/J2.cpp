#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
	int dice1, dice2, dice3, dice4,total;
	cin >> dice1 >> dice2;
	dice3 = min(dice1, dice2);
	dice4 = max(dice1, dice2);
	if (dice3 > 9)
	{
		dice3 = 9;
		dice4 = 9;
	}
	if (dice4 > 9)
		dice4 = 9;
	if (dice3 + dice4 < 10)
		total = 0;
	else
		total = dice3 + dice4 - 9;
	if (total != 1)
		cout << "There are " << total << " ways to get the sum 10.";
	else
		cout << "There is 1 way to get the sum 10.";
	return 0;
}