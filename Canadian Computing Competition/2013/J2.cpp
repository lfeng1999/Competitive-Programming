#include <iostream>
#include <string>

using namespace std;

int main()
{
	char num[8] = "SHIONZX";

	string sign;
	cin >> sign;

	int p = 1;
	for (int i = 0; i!=sign.length(); ++i)
	{
		int j = 0;
		for (int k = 0; k != 7; ++k)
		if ((char)sign[i] == num[k])
			j = 1;
		if (!j)
			p = 0;
	}

	if (p)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}