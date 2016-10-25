#include <iostream>
#include <fstream>

using namespace std;

int cycle[20];

int main()
{
	//ifstream file;
	//file.open("globalwarming.txt");
	int N = 0, csize = 0;
	cin >> N;
	//file >> N;
	while (N)
	{

			for (int i = 0; i != N; ++i)
			{
				cin >> cycle[i];
			//	file >> cycle[i];
			}
			if (N == 1)
				cout << 0 << endl;
			else
			{
				bool work = true;
				for (int size = 1; size != N; ++size)
				{
					work = true;
					int constant = cycle[size] - cycle[0];
					for (int start2 = 0; start2 + size < N; ++start2)
					for (int start = start2; start + size < N && work; start += size)
					{
						if (cycle[start + size] - cycle[start] != constant)
						{
							work = false;
						}
					}
					if (work)
					{
						cout << size << endl;
						break;
					}
				}
			}
		cin >> N;
		//file >> N;
	}

	return 0;
}