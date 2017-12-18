#include <bits/stdc++.h>

using namespace std;

const int mult = 410, maxN = 20;
int n;
int g[mult][mult];

bool rpast[mult][mult], cpast[mult][mult], sq[20][20][mult];

bool curpast[mult];
bool finished[mult][mult];
int vals[mult], amt[mult][mult];

int main(){
	freopen("09.in","r",stdin);
	freopen("output_09.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	srand(time(NULL));
	cin >> n;
	int curempt = 0;
	for (int i=0; i<n*n; ++i){
		for (int j=0; j<n*n; ++j){
			cin >> g[i][j];
			rpast[i][g[i][j]] = cpast[j][g[i][j]] = true;
			sq[i/n][j/n][g[i][j]] = true;
			if (g[i][j] == 0) curempt++;
		}
	}
	set<pair<int,pair<int,int>>> V;
	for (int i=0; i<n*n; ++i){
		for (int j=0; j<n*n; ++j){
			if (g[i][j] != 0) continue;
			int curtot = 0;
			for (int v = 1; v<=n*n; ++v){
				if (rpast[i][v] || cpast[j][v] || sq[i/n][j/n][v]) continue;
				++curtot;
			}
			amt[i][j] = curtot;
			V.insert(make_pair(curtot, make_pair(i, j)));
		}
	}
	int empt = 0;
	while (!V.empty()){
		auto it = *V.begin(); V.erase(V.begin());
		int i = it.second.first, j = it.second.second;
		int tot = 0;
		for (int v = 1; v<=n*n; ++v){
			if (rpast[i][v] || cpast[j][v] || sq[i/n][j/n][v]) continue;
			vals[tot++] = v;
		}
		if (tot == 0){
			empt++;
			continue;
		}
		int v = vals[rand()%tot];
		for (int j2=0; j2<n*n; ++j2){
			if (j == j2) continue;
			if (V.count(make_pair(amt[i][j2], make_pair(i, j2))) && !cpast[j2][v] && !sq[i/n][j2/n][v] && !rpast[i][v]){
				V.erase(make_pair(amt[i][j2], make_pair(i, j2)));
				amt[i][j2]--;
				V.insert(make_pair(amt[i][j2]-1, make_pair(i, j2)));
			}
		}

		for (int i2=0; i2<n*n; ++i2){
			if (i == i2) continue;
			if (V.count(make_pair(amt[i2][j], make_pair(i2, j))) && !cpast[j][v] && !sq[i2/n][j/n][v] && !rpast[i2][v]){
				V.erase(make_pair(amt[i2][j], make_pair(i2, j)));
				amt[i2][j]--;
				V.insert(make_pair(amt[i2][j]-1, make_pair(i2, j)));
			}
		}
		for (int i2=n*int(i/n); i2 < (n+1)*int(i/n); ++i2){
			for (int j2=n*int(j/n); j2 < (n+1)*int(j/n); ++j2){
				if (i == i2 && j == j2) continue;
				if (V.count(make_pair(amt[i2][j2], make_pair(i2, j2))) && !cpast[j2][v] && !sq[i2/n][j2/n][v] && !rpast[i2][v]){
					V.erase(make_pair(amt[i2][j2], make_pair(i2, j2)));
					amt[i2][j2]--;
					V.insert(make_pair(amt[i2][j2]-1, make_pair(i2, j2)));
				}		
			}	
		}
		rpast[i][v] = cpast[j][v] = sq[i/n][j/n][v] = true;
		g[i][j] = v;
	}
	cout << double(empt) / double(curempt) << endl;
	for (int i=0; i<n*n; ++i){
		for (int j=0; j<n*n; ++j){
			cout << g[i][j] << " ";
		}
		cout << '\n';
	}
	// cout << empt << endl;
	return 0;
}