#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIPII;
#define INF 0x3f
#define INF2 0x7fffffff
#define mp make_pair
#define pb push_back

vector<pair<int, int>> vals;
int N, Q, a, b, q;
int v[200010], n[200010];

int main()
{
	for (int i = 0; i != 200010; ++i)
		v[i] = INF2, n[i] = INF2;
	vals.push_back(mp(-1000000001, 0));
	vals.push_back(mp(1000000001, 0));
	//ifstream file("Intervals.txt");
	cin >> N >> Q;
	for (int i = 0; i != N; ++i)
	{
		cin >> a >> b;
		vals.push_back(mp(a, 1));
		vals.push_back(mp(b+1, -1));
	}
	sort(vals.begin(), vals.end());
	for (int i = 1; i != vals.size(); ++i)
		vals[i].second += vals[i - 1].second;
	for (int i = 0; i != vals.size(); ++i)
	{
		n[i] = vals[i].first;
		v[i] = vals[i].second;
		//cout << n[i] << " " << v[i] << endl;
	}
	for (int i = 0; i != Q; ++i)
	{
		cin >> q;
		cout << v[upper_bound(n, n + 200009, q) - n - 1] << endl;
	}
	return 0;
}