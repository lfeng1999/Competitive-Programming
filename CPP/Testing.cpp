#include <bits/stdc++.h>

using namespace std;

typedef pair<int,pair<int,int>> pipii;
typedef pair<int,int> pii;

const int MOD = ((int)1e9) + 7;
int C, R, M, addby[510][510], grid[510][510], data[100010][5], subby[510][510], mv[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
pair<int,int> p[250010];
long long tot[510][510];

class pqsort{
public:
	bool operator () (const pair<int,int> &p, const pair<int,int> &q){
		return grid[p.first][p.second] < grid[q.first][q.second];
	}
};

int main()
{
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> C >> R >> M;

	for (int i=0; i<M; ++i)
	{
		int r,c,w,h,n; cin >> c >> r >> w >> h >> n;
		addby[r][c]+=n;
		addby[r+h][c]-=n;
		addby[r][c+w]-=n;
		addby[r+h][c+w]+=n;
		data[i][0] = c, data[i][1] = r, data[i][2] = w, data[i][3] = h, data[i][4] = n;
	}

	for (int j=1; j<=C; ++j)
	{
		for (int i=1; i<=R; ++i)
		{
			addby[i][j] += addby[i-1][j];
		}
	}
	for (int i=0; i < M; ++i)
	{
		int c = data[i][0], r = data[i][1], w = data[i][2], h = data[i][3], n = data[i][4];
		addby[r+h][c]-=n*h;
		addby[r+h][c+w]+=n*h;
	}



	for (int j=1; j<=C; ++j)
	{
		for (int i=1; i<=R; ++i)
		{
			addby[i][j] += addby[i-1][j];
		}
	}


	for (int i=1; i<=R; ++i)
	{
		for (int j=1; j<=C; ++j)
		{
			addby[i][j] += addby[i][j-1];
		}
	}

	for (int i=0; i<M; ++i)
	{
		int c = data[i][0], r = data[i][1], w = data[i][2], h = data[i][3], n = data[i][4];
		subby[r][c+w]-=n*w;
		subby[r+h][c+w]+=n*w;
	}


	for (int j=1; j<=C; ++j)
	{
		for (int i=1; i<=R; ++i)
		{
			subby[i][j] += subby[i-1][j];	
		}
	}

	for (int i=0; i<M; ++i)
	{
		int c = data[i][0], r = data[i][1], w = data[i][2], h = data[i][3], n = data[i][4];
		subby[r+h][c+w]+=n*w*h;
	}


	for (int j=1; j<=C; ++j)
	{
		for (int i=1; i<=R; ++i)
		{
			subby[i][j] += subby[i-1][j];	
		}
	}

	for (int i=1; i<=R; ++i)
	{
		for (int j=1; j<=C; ++j)
		{
			addby[i][j] += subby[i][j];
		}
	}

	for (int i=1; i<=R; ++i)
	{
		for (int j=1; j<=C; ++j)
		{
			addby[i][j] += addby[i][j-1];
		}
	}

	for (int i=1; i<=R; ++i)
	{
		for (int j=1; j<=C; ++j)
		{
			grid[i][j] = addby[i][j];
		}
	}

	int r, c;
	cin >> c >> r;

	for (int i=1; i<=R; ++i)
	{
		for (int j=1; j<=C; ++j)
		{
			p[(i-1)*C+j-1] = make_pair(i, j);
		}
	}
	sort(p, p+R*C, pqsort());

	for (int i=1; i<=R; ++i)
		fill(tot[i], tot[i]+C, -(long long)1e18);
	tot[r][c] = grid[r][c];
	
	long long best = 0;

	for (int i=0; i<R*C; ++i){
		r = p[i].first, c = p[i].second;
		if (tot[r][c] == (int)-1e9) continue;
		best = max(best, tot[r][c]);
		for (int j=0; j<4; ++j){
			int nr = r + mv[j][0], nc = c + mv[j][1];
			if (nr < 1 || nr > R || nc < 1 || nc > C) continue;
			if (grid[r][c] < grid[nr][nc])
				tot[nr][nc] = max(tot[nr][nc], tot[r][c] + grid[nr][nc]);
		}
	}
	cout << best % MOD<< endl;


	return 0;
}