#include <iostream>
#include <math.h> 

using namespace std;


int check(int t, int h)
{
	bool mybool = true;
	int value = -6 * pow(t,4) + h*pow(t,3) + 2 * pow(t,2) + t;
	if (value > 0)
		mybool = true;
	else
		mybool = false;
	return mybool;
}


int main()
{
	int time,humid,tcount=1;
	cin >> humid >> time;
	while (check(tcount, humid)&&tcount<time+1)
	{
		tcount++;
	}
	if (tcount>time)
		cout << "The balloon does not touch ground in the given time.";
	else
		cout << "The balloon first touches ground at hour:" <<endl<< tcount;
	return 0;
}