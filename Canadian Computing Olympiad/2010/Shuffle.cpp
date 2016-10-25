#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

map<char, char> mydict;

int N = 0;

char translate(char letter)
{
	vector<char> passed;
	int count = 0;
	while (find(passed.begin(), passed.end(), letter) == passed.end() && count <= N)
	{
		passed.push_back(letter);
		++count;
		letter = mydict[letter];
	}
	return passed[N%count];
}

int main()
{
	//ifstream file("Shuffle.txt");
	char val;
	for (int i = 0; i != 26; ++i)
	{
		cin >> val;
		mydict[65 + i] = val;
	}
	cin >> val;
	mydict['_'] = val;
	cin >> N;
	string phrase;
	cin >> phrase;
	for (int i = 0; i != phrase.length(); ++i)
		cout << translate(char(phrase[i]));

	return 0;
}