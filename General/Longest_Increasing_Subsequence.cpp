#include <iostream>

using namespace std;

int nums[5001];

int main()
{
	int N = 0;
	scanf("%d", &N);
	int count = 0;
	for (int i = 0; i != N; ++i)
	{
		int val = 0;
		scanf("%d", &val);
		if (val > nums[count])
		{
			nums[count + 1] = val;
			count++;
		}
		else
			for (int i = 0; i <= count; ++i)
			{
				if (val > nums[i] && val < nums[i + 1])
					nums[i + 1] = val;
			}
	}
	printf("%d", count);
	return 0;
}