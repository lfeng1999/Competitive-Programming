#include <bits/stdc++.h>

using namespace std;

float degree[1001];

int main()
{
	int N = 0;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		string name;
		cin >> name >> degree[i];	
	}
	sort(degree, degree + N);
	float mdeg = 360 - degree[N - 1] + degree[0];
	for (int i = 1; i != N; ++i)
		mdeg = max(mdeg, degree[i] - degree[i - 1]);
	cout << ceil((360 - mdeg) * 12.0);
	return 0;
}