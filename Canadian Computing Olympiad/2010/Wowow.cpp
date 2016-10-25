#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2500005;
int N, mov, X, R, bit[MAXN], a[MAXN], b[MAXN];
char id[MAXN];
vector<int> idk;
unordered_map<int, int> comp, decomp, rating, rrating;
//     rating, compressed | friend, compressed rating
void update(int x, int val)
{
	for (; x < MAXN; x += x&-x)
	{
		bit[x] += val;
	}
}

int query(int x)
{
	int tot = 0;
	for (; x>0; x -= x&-x)
	{
		tot += bit[x];
	}
	return tot;
}

int binary_search(int val)
{
	int low = 0, high = idk.size() + 1;
	while (high > low)
	{
		int mid = (low + high) / 2;
		if (query(mid) >= val)
		{
			high = mid;
		}
		else
		{
			low = mid + 1;
		}
	}
	return rrating[decomp[low]];
}

int main()
{
//	freopen("Wowow.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf(" %c%d", &id[i], &a[i]);
		if (id[i] == 'N' | id[i] == 'M')
		{
			scanf("%d", &b[i]);
			idk.push_back(b[i]);
			rrating[b[i]] = a[i];
		}
	}
	sort(idk.begin(), idk.end());
	reverse(idk.begin(), idk.end());
	for (int i = 1; i <= idk.size(); ++i)
	{
		comp[idk[i - 1]] = i;
		decomp[i] = idk[i - 1];
	}
	for (int i = 0; i != N; ++i)
	{
		if (id[i] == 'N')
		{
			update(comp[b[i]], 1);
			rating[a[i]] = comp[b[i]];
		}
		else if (id[i] == 'M')
		{
			update(rating[a[i]], -1);
			update(comp[b[i]], 1);
			rating[a[i]] = comp[b[i]];
		}
		else if (id[i] == 'Q')
		{
	//		cout << "DAFUQ";
			printf("%d\n",binary_search(a[i]));
		}
	}

	return 0;
}