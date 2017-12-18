#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef pair<int,int> pii;
const double eps = 1e-8;
bool eq(double a, double b){return fabs(a-b) < eps;}
int N, dp[2010][2010];
vector<int> ys;
double slope(double x1, double y1, double x2, double y2){
	return (y2 - y1) / (x2 - x1);
}



int solve(int L, int R){
	if (L > R) return 0;
	else if (L == R) return 1;
	// cout << "UGH";
	if (dp[L][R] != -1) return dp[L][R];

	dp[L][R] = 1;
	int maxval = 0;
	for (int i=L; i<=R; ++i){
		maxval = max(maxval, ys[i]);
	}
	vector<int> idxes;
	idxes.push_back(L-1);
	for (int i=L; i<=R; ++i){
		if (ys[i] == maxval){
			idxes.push_back(i);
		}
	}
	idxes.push_back(R+1);
	int tmptot = 0;
	for (int i=1; i<idxes.size(); ++i){
		tmptot += solve(idxes[i-1]+1, idxes[i]-1);
	}
	dp[L][R] = max(dp[L][R], tmptot);
	for (int i=1; i<idxes.size()-1; ++i){
		int curtot = 1 + tmptot;
		curtot -= solve(idxes[i-1]+1, idxes[i] - 1);
		curtot -= solve(idxes[i]+1, idxes[i+1] - 1);
		int beg = idxes[i];

		double minslope = (1e9) + 10;
		int x = idxes[i];
		for (int j=beg-1; j > idxes[i-1]; --j){
			double curslope = slope(beg, ys[beg], j, ys[j]);
			if (eq(curslope, minslope) || curslope < minslope){
				curtot += solve(j+1, x-1);
				x = j;
				minslope = curslope;
			}
		}
		curtot += solve(idxes[i-1]+1, x-1);


		double maxslope = -(1e9) - 10;
		x = idxes[i];
		for (int j=beg+1; j < idxes[i+1]; ++j){
			double curslope = slope(beg, ys[beg], j, ys[j]);
			if (eq(curslope, maxslope) || curslope > maxslope){
				curtot += solve(x+1, j-1);
				x = j;
				maxslope = curslope;
			}
		}
		curtot += solve(x+1, idxes[i+1] - 1);


		dp[L][R] = max(dp[L][R], curtot);
	}

	return dp[L][R];
}

int maximum_deevs(vector<int> newys){
	ys = newys;
	N = ys.size();
	for (int i=0; i<2010; ++i) fill(dp[i], dp[i] + 2010, -1);

	return solve(0, N-1);
}

// int main(){
// 	// freopen("test.txt","r",stdin);
// 	cin.sync_with_stdio(0); cin.tie(0);
// 	vector<int> cy;
// 	cin >> N;
// 	for (int qq=0; qq<N; ++qq){
// 		int y; cin >> y; cy.push_back(y);
// 	}
// 	cout << maximum_deevs(cy) << endl;
// 	return 0;
// }