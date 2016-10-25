#include <set>
#include <iostream>

using namespace std;

#define rint(a) scanf("%d",&a)

set<int> p;
int G, P, pp;


int main()
{
	rint(G);
	rint(P);
	for (int i = 1; i <= G; ++i)
		p.insert(p.end(),i);
	for (int i = 0; i != P; ++i)
	{
		rint(pp);
		auto it = p.upper_bound(pp);
		if (p.empty() || it == p.begin())
		{
			cout << i;
			return 0;
		}
		p.erase(--it);
	}
	cout << P;
	return 0;
}