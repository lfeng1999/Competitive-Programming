#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int n, x, y, ax[4] = { -1, 0, 0, -1 }, ay[4] = { -1, -1, 0, 0 };

int pow(int num, int exp)
{
	int tot = 1;
	for (int i = 0; i != exp; ++i)
		tot *= num;
	return tot;
}

int sqnum(int x, int y, int size, int mx, int my)
{
	if (mx < x + size && my < y + size)
		return 0;
	else if (my < y + size)
		return 1;
	else if (mx >= x + size && my >= y + size)
		return 2;
	else
		return 3;
}

void dfs(int x, int y, int size, int mx, int my) //bottom left co-ord, square size, missing square co-ord
{// the time when tournament of towns is useful in computer science
//	cout << mx << " " << my << endl;
	if (size == 2)
	{
		for (int i = x; i != x + 2; ++i)
		for (int j = y; j != y + 2; ++j){
			if (i != mx | j != my)
				printf("%d %d ", i, j);
		}
		printf("\n");
		return;
	}
	size /= 2;
	int nx = x + size, ny = y + size, msq = sqnum(x,y,size,mx,my);
	if (msq != 0)
		dfs(x, y, size, nx - 1, ny - 1);
	else
		dfs(x, y, size, mx, my);
	if (msq != 1)
		dfs(nx, y, size, nx, ny - 1);
	else
		dfs(nx, y, size, mx, my);
	if (msq != 2)
		dfs(nx, ny, size, nx, ny);
	else
		dfs(nx, ny, size, mx, my);
	if (msq != 3)
		dfs(x, ny, size, nx - 1, ny);
	else
		dfs(x, ny, size, mx, my);

	for (int i = nx - 1; i != nx + 1; ++i)
	for (int j = ny - 1; j != ny + 1; ++j)
	{
		if (i != nx + ax[msq] || j != ny + ay[msq])
			printf("%d %d ", i, j);
	}
	printf("\n");
}


int main()
{
	//freopen("IOITile.txt", "r", stdin);
	cin >> n >> x >> y;
	dfs(0, 0, pow(2, n), x, y);
	return 0;
}