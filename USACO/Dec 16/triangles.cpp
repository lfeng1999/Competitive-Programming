#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int n, a[310][310], b[310];
vector<pair<int,int>> trees;

lint cross(int i, int k, int j){
	lint vx1 = trees[k].first - trees[i].first, vy1 = trees[k].second - trees[i].second;
	lint vx2 = trees[j].first - trees[i].first, vy2 = trees[j].second - trees[i].second;
	return (vx1*vy2 - vx2*vy1 > 0)? 1:-1;
}

int c[310];

void display(int i){
	cout << trees[i].first << " " << trees[i].second << endl;
}
int main(){
	// freopen("test.txt","r",stdin);
	freopen("triangles.in","r",stdin);
	freopen("triangles.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int qq=0; qq<n; ++qq){
		int x, y; cin >> x >> y;
		trees.push_back({x, y});
	}
	sort(trees.begin(), trees.end());
	for (int i=0;i<trees.size(); ++i){
		for (int j=0; j<trees.size(); ++j){
			if (i == j) continue;
			if (trees[i].first == trees[j].first && trees[i].second > trees[j].second) b[i]++;
		}
	}
	for (int i=0; i<trees.size(); ++i){
		for (int j=i+1; j<trees.size(); ++j){
			int lx= trees[i].first, rx = trees[j].first;
			for (int k=0; k<trees.size(); ++k){
				if (i == k || j == k) continue;
				if (cross(i, k, j) > 0 && trees[i].first < trees[k].first && trees[k].first < trees[j].first){
					a[i][j]++; a[j][i]++;
				}
			}
		}
	}
	for (int i=0; i<trees.size(); ++i){
		int x1 = trees[i].first, y1 = trees[i].second;
		for (int j=i+1; j<trees.size(); ++j){
			int x2 = trees[j].first, y2 = trees[j].second;
			for (int k=j+1; k<trees.size(); ++k){
				int x3 = trees[k].first, y3 = trees[k].second;
				if (x1 != x2 && x2 != x3){
					if (cross(i, j, k) > 0){
						int tot = a[i][k] - a[i][j] - a[j][k];
						tot--; //don't include j
						tot -= b[j]; //subtract below j
						c[tot]++;
					}
					else{
						int tot = a[i][j] + a[j][k] - a[i][k];
						int tj = j - 1;
						if (x2 == trees[tj].first){ //fuck it might be below
							if (cross(i, tj, k) > 0)
								tot++;
						}
						c[tot]++;
					}
				}
				else if (x1 == x2){
					int tot = a[j][k] - a[i][k];
					c[tot]++;
				}
				else if (x2 == x3){
					int tot = a[i][k] - a[i][j];
					c[tot]++;
				}
			}
		}
	}
	for (int i=0; i<=n-3; ++i){
		cout << c[i] << '\n';
	}
	return 0;
}