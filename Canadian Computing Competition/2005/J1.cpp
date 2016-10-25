#include <iostream>
#include <cmath>

using namespace std;


int main()
{
	int day,eve,week;
	float costA, costB;
	costA = 0;
	costB = 0;
	cin >> day >> eve >> week;
	if (day > 100){
		costA = (day - 100) * 25;
	}
	if (day > 250){
		costB = (day - 250) * 45;
	}
	costA = costA + eve * 15;
	costB = costB + eve * 35;
	costA = costA + week * 20;
	costB = costB + week * 25;
	cout << "Plan A costs " << costA/100 <<endl << "Plan B costs " << costB/100 << endl;
	if (costB < costA){
		cout << "Plan B is cheapest.";
	}
	else if (costA < costB){
		cout << "Plan A is cheapest.";
	}
	else
		cout << "Plan A and B are the same price.";
	return 0;
}
