#include <iostream>
#include <vector>

using namespace std;

#define MAXN 1000010

int bales[MAXN], jumps[MAXN], N;
vector<int> mh;


int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", bales + i);
	for (int i = 0; i < N; ++i)
		scanf("%d", jumps + i);
	for (int i = N - 1; i >= 0; --i)
	{
		while (mh.size() && bales[i] >= mh.back())
			mh.pop_back();
		mh.push_back(bales[i]);
		if (jumps[i] >= mh.size())
			bales[i] = -1;
		else
			bales[i] = mh[mh.size() - jumps[i] - 1];
	}
	for (int i = 0; i != N; ++i)
		printf("%d ", bales[i]);
	return 0;
}