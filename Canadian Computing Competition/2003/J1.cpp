#include <iostream>
#include <string>

using namespace std;

void deg(int size, string name)
{
	for (int i = 0; i < size; ++i)
		cout << name;
}

int main()
{
	int height, space, handle;
	cin >> height >> space >> handle;
	for (int count = 1; count <= height; count++)
	{
		cout << "*";
		deg(space," ");
		cout << "*";
		deg(space, " ");
		cout << "*" <<  endl;
	}
	deg(space * 2 + 3, "*");
	cout << endl;
	for (int count = 1; count <= handle; count++)
	{
		deg(space+1, " ");
		cout << "*";
		deg(space+1, " ");
		cout << endl;
	}
	return 0;
}

