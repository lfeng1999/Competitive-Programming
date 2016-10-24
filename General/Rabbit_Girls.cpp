#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int N = 0, K = 0;
	cin >> N >> K;
	if (K > N)
		cout << K - N;
	else
		cout << min(N%K, K - N%K);
	return 0;
}