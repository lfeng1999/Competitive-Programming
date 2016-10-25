#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int house[1001];
int nhouse = 0, nhose = 0;
#define maxn 1000000

int binloop()
{
	int left = 0, right = 1000000;
	while (right - left	> 1)
	{
		int mid = (left + right) / 2;
		int nused = 1;
		int hydrant = mid;
		for (int i = 0; i != nhouse; ++i)
		{
			if (house[i] > hydrant + mid && house[i] < maxn - mid)
			{
				++nused;
				hydrant = house[i] + mid;
			}
		}
		if (nused > nhose)
			left = mid;
		else
			right = mid;

	}
	return right;

}
void update(int nhouse)
{
	house[nhouse] = house[0];
	for (int i = 0; i != nhouse; ++i)
	{
		house[i] = house[i + 1] - house[nhouse];
	}
	house[nhouse] = 0;
}




int main()
{
	//ifstream file("Firehose.txt");
	cin >> nhouse;
	for (int i = 0; i != nhouse; ++i)
	{
		cin >> house[i];
	}
	sort(house, house + nhouse);
	cin >> nhose;

	if (nhose >= nhouse)
	{
		cout << 0;
		exit(0);
	}

	int mlength = 0;
	for (int i = 0; i != nhouse; ++i)
	{
		update(nhouse);
		mlength = max(mlength, binloop());
	}
	cout << mlength;
	return 0;
}