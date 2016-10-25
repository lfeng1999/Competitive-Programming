#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

string ending(int n)
{
	if (n % 10 == 1 && (n / 10) % 10 != 1)
		return "st";
	if (n % 10 == 2 && (n / 10) % 10 != 1)
		return "nd";
	if (n % 10 == 3 && (n / 10) % 10 != 1)
		return "rd";
	else
		return "th";

}

int main()
{
	//ifstream file("Common Words.txt");
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i != n; ++i)
	{
		map<string, int> mydict;
		int m, k;
		string word;
		scanf("%d%d",&m, &k);
		for (int i = 0; i != m; ++i)
		{
			cin >> word;
			mydict[word]++;
		}
		vector<pair<int, string>> wcount;
		for (map<string, int>::const_iterator iter = mydict.begin(); iter != mydict.end(); ++iter)
			wcount.push_back(make_pair(iter->second, iter->first));
		sort(wcount.begin(), wcount.end());
		reverse(wcount.begin(), wcount.end());
		cout << k << ending(k) << " most common word(s):" << endl;
		int val = 0, counter = 0;
		int j = 0;
		for (int i = 0; i != wcount.size();)
		{
			for ( j = i ; j != wcount.size() && wcount[j].first == wcount[i].first; ++j)
			{
				if (i == k - 1)
					cout << wcount[j].second << endl;
			}
			i = j;
		}
		cout << endl;
	}
	return 0;
}