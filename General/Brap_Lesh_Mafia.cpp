#include <iostream>

using namespace std;

int main()
{
	long long N = 0, K = 0;
	long long total = 0;
	cin >> N >> K;
	for (int i = 0; i != N; ++i)
	{
		long long a, b;
		cin >> a >> b;
		total += ((a%K)*(b%K))%K;
		total = total%K;
	}
	cout << total;
	return 0;
}