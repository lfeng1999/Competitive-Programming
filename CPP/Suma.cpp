#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> graph[500000];
int N, grid[710][710], grow[710][710];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=1; i<=N; ++i){
		for (int j=1; j<=N; ++j){
			cin >> grid[i][j];
		}
	}
	for (int i=1; i<=N; ++i){
		for (int j=1; j<=N; ++j){
			cin >> grow[i][j];
		}
	}


	return 0;
}