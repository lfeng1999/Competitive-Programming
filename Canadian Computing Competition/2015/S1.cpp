#include <iostream>
#include <vector>

using namespace std;

#define rint(a) scanf("%d",&a)

vector<int> x;
int K, a;

int main()
{
	rint(K);
	for (int i = 0; i != K; ++i)
	{
		rint(a);
		if (a==0){
		if (x.size())
			x.pop_back();
			}
		else
			x.push_back(a);
	}
	int tot = 0;
	for (int i = 0; i != x.size(); ++i)
		tot += x[i];
	cout << tot;
	return 0;
}