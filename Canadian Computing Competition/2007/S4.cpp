#include <iostream>
#include <vector>
#include <algorithm>

int fin[10002];

using namespace std;

int main()
{
	vector<pair<int, int>> slide;
	int N = 0;
	cin >> N;
	int s1 = 10, s2 = 10;
	cin >> s1 >> s2;
	int len = 0;
	while (s1 | s2)
	{
		++len;
		slide.push_back(pair<int, int>(min(s1, s2), max(s1, s2)));
		cin >> s1 >> s2;
	}
	sort(slide.begin(), slide.end());
	fin[1] = 1;
	for (int i = 0; i != len; ++i)
	{
		fin[slide[i].second] += fin[slide[i].first];
	}

	cout << fin[N];

	return 0;
}