#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;


string namelist[10000];
int treesize[10000];

int main()
{
	int L = 0, N = 0;
	//ifstream file("PyramidMessage.txt");
	//file >> L;
	cin >> L;
	for (int i = 0; i != L; ++i)
	{
		for (int i = 0; i != 10000; ++i)
		{
			treesize[i] = 0;
		}
		map<string, int> names;
		int counter = 1;
		int mtree = 0;
		//file >> N;
		cin >> N;
		for (int i = 1; i != N+1; ++i)
		{
			//file >> namelist[i];
			cin >> namelist[i];
		}
		namelist[0] = namelist[N];
		for (int i = 0; i != N; ++i)
		{
			if (names.find(namelist[i]) == names.end())
			{
				names.insert(names.end(), pair<string, int>(namelist[i], counter));
				++counter;
			}
			if (i >= 1)
			{
				if (names[namelist[i]] > names[namelist[i - 1]])
				{
					treesize[names[namelist[i]]] = treesize[names[namelist[i - 1]]] + 1;
				}
			}
		}
		for (int i = 0; i != names.size()+2; ++i)
		{
			mtree = max(mtree, treesize[i]);
		}
		cout << N * 10 - mtree * 20 << endl;
	}
	return 0;
}