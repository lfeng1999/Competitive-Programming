#include <iostream>
#include <string>

using namespace std;

int main()
{
	string word;
	cin >> word;
	while (word != "X")
	{
		while (word.find("ANA") != string::npos | word.find("BAS") != string::npos)
		{
			if (word.find("ANA") != string::npos)
				word.replace(word.find("ANA"), 3, "A");
			if (word.find("BAS") != string::npos)
				word.replace(word.find("BAS"), 3, "A");
		}
		if (word == "A")
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
		cin >> word;
	}
	return 0;
}