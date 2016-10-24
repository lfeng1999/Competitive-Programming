#include <iostream>
#include <algorithm>

int nums[100000];

using namespace std;

int main()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int N = 0;
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> nums[i];
	
	nums[2] += nums[0];
	for (int i = 3; i < N; i++)
		nums[i] += max(nums[i-2], nums[i-3]);
	cout << max(nums[N - 1], nums[N - 2]);

	return 0;
}
