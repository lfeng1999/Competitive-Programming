#include <iostream>
#include <fstream>

using namespace std;

int N, pins[100001], npins[100001];
double inversions = 0;

void merge(int L, int R)
{
	int mid = (L + R) / 2;
	int s1 = L, s2 = mid + 1, pos = L;
	while (s1 <= mid | s2 <= R)
	{
		if ((s1 <= mid && s2 <= R) | s2>R)
		{
			if ((pins[s1] <= pins[s2]) | s2>R)
			{
				npins[pos] = pins[s1];
				pos++;
				s1++;
			}
			else
			{
				npins[pos] = pins[s2];
				pos++;
				s2++;
				inversions += mid + 1 - s1;
			}
		}
		else if (s1 > mid)
		{
			npins[pos] = pins[s2];
			pos++;
			s2++;
		}
	}
	for (int i = L; i <= R; ++i)
		pins[i] = npins[i];
}


void mergesort(int L, int R)
{
	if (L == R)
		return;
	int mid = (L + R) / 2;
	mergesort(L, mid);
	mergesort(mid + 1, R);
	merge(L, R);
}

int main()
{
	//ifstream file("Pinball.txt");
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
		scanf("%d", &pins[i]);
	mergesort(0, N - 1);
	printf("%.2f", double(inversions + N) / N);
	return 0;
}