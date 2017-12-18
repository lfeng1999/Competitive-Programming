#include <bits/stdc++.h>

using namespace std;

struct Rect{
	int x1, y1, x2, y2;
};

struct BIT{
	int tree[100010];
	int query(int i){
		int ret = 0;
		for (; i > 0; i -= i&(-i))
			ret += tree[i];
		return ret;
	}
	void update(int i, int val){
		if (i <= 0) return;
		for (; i < 100010; i += i&(-i))
			tree[i] += val;
	}
} bit;


int n, k, m, grid[2510][2510];
bool blocked[96000010];
int ulx, urx, uly, ury;

void flood(int v, int lx, int rx, int ly, int ry){
	if (urx < lx || rx < ulx || ury < ly || ry < uly || blocked[v]) return;
	if (lx == rx && ly == ry){
		bit.update(grid[lx][ly], -1);
		blocked[v] = true;
		return;
	}
	int midx = (lx + rx)/2, midy = (ly + ry)/2;
	blocked[v] = true;
	flood(v*4, lx, midx, ly, midy);
	blocked[v] &= blocked[v*4];
	if (lx != rx){
		flood(v*4+1, midx+1, rx, ly, midy);
		blocked[v] &= blocked[v*4+1];
	}
	if (ly != ry){
		flood(v*4+2, lx, midx, midy+1, ry);
		blocked[v] &= blocked[v*4+2];
	}
	if (lx != rx && ly != ry){
		flood(v*4+3, midx+1, rx, midy+1, ry);
		blocked[v] &= blocked[v*4+3];
	}
}


int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k >> m;
	for (int qq=0; qq<m; ++qq){
		int si; cin >> si;
		vector<Rect> r1, r2, r3, r4;
		for (int kk=0; kk<si; ++kk){
			int sx, sy; cin >> sx >> sy;
			int ex = min(sx + k - 1, n), ey = min(sy + k - 1, n);
			r1.push_back({sx, sy, ex, ey});
		}
		for (int i=0; i<si; ++i){
			for (int j=i+1; j<si; ++j){
				int sx, sy, ex, ey; 
				sx = max(r1[i].x1, r1[j].x1); ex = min(r1[i].x2, r1[j].x2);
				sy = max(r1[i].y1, r1[j].y1); ey = min(r1[i].y2, r1[j].y2);
				if (sx > ex || sy > ey) continue;
				r2.push_back({sx, sy, ex, ey});
				for (int k=j+1; k<si; ++k){
					int sx2, sy2, ex2, ey2;
					sx2 = max(sx, r1[k].x1), ex2 = min(ex, r1[k].x2);
					sy2 = max(sy, r1[k].y1), ey2 = min(ey, r1[k].y2);
					if (sx2 > ex2 || sy2 > ey2) continue;
					r3.push_back({sx2, sy2, ex2, ey2});

					for (int l=k+1; l<si; ++l){
						int sx3, sy3, ex3, ey3;
						sx3 = max(sx2, r1[l].x1), ex3 = min(ex2, r1[l].x2);
						sy3 = max(sy2, r1[l].y1), ey3 = min(ey2, r1[l].y2);
						if (sx3 > ex3 || sy3 > ey3) continue;
						r4.push_back({sx3, sy3, ex3, ey3});
					}
				}
			}
		}
		for (auto &it : r1){
			int sx = it.x1, ex = it.x2, sy = it.y1, ey = it.y2;
			grid[sx][sy]++; grid[ex+1][sy]--; grid[sx][ey+1]--; grid[ex+1][ey+1]++;
		}
		for (auto &it : r2){
			int sx = it.x1, ex = it.x2, sy = it.y1, ey = it.y2;
			grid[sx][sy]--; grid[ex+1][sy]++; grid[sx][ey+1]++; grid[ex+1][ey+1]--;
		}
		for (auto &it : r3){
			int sx = it.x1, ex = it.x2, sy = it.y1, ey = it.y2;
			grid[sx][sy]++; grid[ex+1][sy]--; grid[sx][ey+1]--; grid[ex+1][ey+1]++;
		}
		for (auto &it : r4){
			int sx = it.x1, ex = it.x2, sy = it.y1, ey = it.y2;
			grid[sx][sy]--; grid[ex+1][sy]++; grid[sx][ey+1]++; grid[ex+1][ey+1]--;
		}
	}
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=n; ++j){
			grid[i][j] += grid[i][j-1];
		}
	}
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=n; ++j){
			grid[j][i] += grid[j-1][i];
		}
	}
	for (int i=k; i<=n; ++i){
		for (int j=k; j<=n; ++j){
			bit.update(grid[i][j], 1);
		}
	}
	int QQ; cin >> QQ;
	for (int qq=0; qq<QQ; ++qq){
		int typ; cin >> typ;
		if (typ == 1){
			int sx, sy; cin >> sx >> sy;
			int ex = min(sx + k - 1, n), ey = min(sy + k - 1, n);
			ulx = sx, urx = ex; uly = sy, ury = ey;
			flood(1, k, n, k, n);
		}
		else if (typ == 2){
			int V; cin >> V;
			if (V > m){
				printf("%.7f\n", 0.0);
				continue;
			}
			double perc = double(bit.query(m) - bit.query(V-1))/double((n-k+1)*(n-k+1));
			printf("%.7f\n", perc);
		}
	}
	return 0;
}