#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<pair<int, pair<int,int> > > path; // position.... l or r money

int main()
{
	ifstream file("Zihao.txt");
	int l = 0, r = 0, n = 0, t = 0;
	cin >> n >> t;
	for (int i = 0; i != n; ++i)
	{
		int p = 0, x = 0, s = 0;
		cin >> p >> x >> s;
		path.push_back(make_pair(p, make_pair(s, x)));
	}
	sort(path.begin(), path.end());

	if (path[0].second.first == 0)
	{
		l = path[0].second.second;
		r = path[0].second.second - t;
	}
	else
	{
		r = path[0].second.second - t;
	}
	//cout << l << " " << r << endl;
	for (int i = 1; i != path.size(); ++i)
	{
		if (path[i].second.first == 0)
		{
			l = max(l + path[i].second.second, r + path[i].second.second - t);
		}
		else
		{
			r = max(r + path[i].second.second, l + path[i].second.second - t);
		}
		//cout << l << " " << r << endl;
	}
	cout << max(l, r);
	return 0;
}