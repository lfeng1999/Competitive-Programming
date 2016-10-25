#include <iostream>

using namespace std;


int main()
{
	int first,others,last;
	cin >> first >> last;
	for (first; first <= last; first = first + 60){
		cout << "All positions change in year " << first << endl;
	}
	return 0;
}
