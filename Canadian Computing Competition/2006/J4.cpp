#include <iostream>
#include <vector>

using namespace std;

int find(int arr[], int len, int seek)
{
	for (int i = 1; i < len+1; ++i)
	{
		if (arr[i] == seek) return i;
	}
	return -1;
}

int main()
{
	int vsize = 5;
	vector<pair<int, int>> conditions;
	conditions.push_back(pair<int, int>(1, 7));
	conditions.push_back(pair<int, int>(1, 4));
	conditions.push_back(pair<int, int>(2, 1));
	conditions.push_back(pair<int, int>(3, 4));
	conditions.push_back(pair<int, int>(3, 5));

	int before = 0, after = 0;
	cin >> before >> after;
	while (before && after)
	{
		conditions.push_back(pair<int, int>(before, after));
		cin >> before >> after;
		++vsize;
	}



	int a[8];
	bool finish = false;

	for (a[1] = 1; a[1] != 8; ++a[1]){
		for (a[2] = 1; a[2] != 8; ++a[2]){
			if (a[2] != a[1])
			for (a[3] = 1; a[3] != 8 ; ++a[3]){
				if (a[3] != a[1] && a[3] != a[2])
				for (a[4] = 1; a[4] != 8 ; ++a[4]){
					if (a[4] != a[1] && a[4] != a[2] && a[4] != a[3])
					for (a[5] = 1; a[5] != 8; ++a[5]){
						if (a[5] != a[1] && a[5] != a[2] && a[5] != a[3] && a[5] != a[4])
						for (a[6] = 1; a[6] != 8; ++a[6])
						if (a[6] != a[1] && a[6] != a[2] && a[6] != a[3] && a[6] != a[4] && a[6] != a[5])
						{
							finish = true;
							a[7] = 28 - a[1] - a[2] - a[3] - a[4] - a[5] - a[6];

							for (int i = 0; i != vsize; ++i)
							{
								if (find(a, 7, conditions[i].first) > find(a, 7, conditions[i].second))
									finish = false;
							}
							if (finish)
								break;

						}
						if (finish)
							break;
					}
					if (finish)
						break;
				}
				if (finish)
					break;
			}
			if (finish)
				break;
		}
		if (finish)
			break;
	}

	if (finish)
		cout << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " " << a[5] << " " << a[6] << " " << a[7];
	else
		cout << "Cannot complete these tasks. Going to bed.";
	return 0;
}