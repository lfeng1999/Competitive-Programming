#include <iostream>
using namespace std;

int main()
{
	int num1, num2, num3;
	cin >> num1;
	cin >> num2;
	cin >> num3;
	if (num1+num2+num3!=180){
		cout << "Error";
	}
	else if (num1==num2 and num1==num3){
		cout << "Equilateral";
	}
	else if (num1==num2 or num2==num3 or num1==num3){
		cout << "Isosceles";
	}
	else{
		cout << "Scalene";
	}
	return 0;
}