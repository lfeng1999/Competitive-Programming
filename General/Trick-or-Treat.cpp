#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int houses[10001];


int main()
{
//	ifstream file("TrickTreat.txt");
	int N = 0, D = 0;
	cin >> N >> D;

	for (int i = 0; i != N; ++i)
		cin >> houses[i];

	sort(houses, houses + N);
	int count = 0;
	while (D - houses[count] >= 0 && count < N)
	{
		D -= houses[count] + 1;
		count++;
	}

	cout << count << endl;
	return 0;
}