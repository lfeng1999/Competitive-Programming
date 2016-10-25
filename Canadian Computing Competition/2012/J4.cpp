#include <iostream>
#include <string>

using namespace std;

int K;
string word;


int main()
{
	cin >> K >> word;
	for (int i = 0; i != word.length(); ++i)
	{
		int x = int(word[i]) - ((3 * (i + 1) + K)%26);
		if (x < 65)
			x += 26;
		cout << char(x);
	}
	return 0;
}