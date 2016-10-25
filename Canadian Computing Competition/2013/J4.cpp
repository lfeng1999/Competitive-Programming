#include <iostream>
#include <list>


using namespace std;

int main()
{
	int tottime=0, cnum=0, tempnum=0, total=0, count=0;
	cin >> tottime >> cnum;
	list<int> chores;
	for (int i=0; i < cnum; i++)
	{
		cin >> tempnum;
		chores.push_back(tempnum);
	}
	chores.sort();
	list<int>::iterator iter;
	for (iter = chores.begin(); iter != chores.end(); ++iter)
	{
		total = total + *iter;
		if (tottime < total)
			break;
		else
			++count;
	}
	cout << count;
	return 0;
}