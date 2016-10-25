#include <iostream>
#include <map>

using namespace std;

#define rchar(a) scanf(" %c", &a)
#define rint(a) scanf("%d", &a)

map<char, int> shirts;

int J, A;
int mshirts[1000010];

int main()
{
	shirts['S'] = 1;
	shirts['M'] = 2;
	shirts['L'] = 3;
	rint(J);
	rint(A);
	for (int i = 1; i <= J; ++i)
	{
		char a;
		rchar(a);
		mshirts[i] = shirts[a];
	}
	int counter = 0;
	for (int i = 1; i <= A; ++i)
	{
		char a;
		int b;
		rchar(a);
		rint(b);
		if (mshirts[b] >= shirts[a])
		{
			counter++;
			mshirts[b] = 0;
		}
	}
	cout << counter;
	return 0;
}