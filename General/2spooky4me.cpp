#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

map<int, int> street;

int main()
{
	//ifstream file("Spooky.txt");
	int N, L, S;
	scanf("%d%d%d", &N, &L, &S);


	for (int i = 0; i != N; ++i)
	{
		int a, b, s;
		scanf("%d%d%d", &a, &b, &s);
		if (street.count(a))
			street[a] += s;
		else
			street[a] = s;
		if (street.count(b + 1))
			street[b + 1] -= s;
		else
			street[b + 1] = -s;
	}

	int Lspook = 0, length = 0;
	map<int, int>::const_iterator iter;

	for (iter = street.begin(); iter != street.end(); ++iter)
	{
		Lspook += iter->second;
		if (Lspook >= S)
		{
			length += (++iter)->first - (--iter)->first;
		}
	}
	cout << L - length;


	return 0;
}