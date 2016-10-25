#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;


int main()
{
	int antennas;
	int eyes;
	cin >> antennas;
	cin >> eyes;
	if ((antennas >= 3) && (eyes <= 4))
	{
		cout << "TroyMartian" << endl;
	}
	if ((antennas <= 6) && (eyes >= 2))
	{
		cout << "VladSaturnian" << endl;
	}
	if ((antennas <= 2) && (eyes <= 3))
	{
		cout << "GraemeMercurian" << endl;
	}
	return 0;
}