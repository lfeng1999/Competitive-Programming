#include <bits/stdc++.h>

using namespace std;

map<int,int> pos[5];
int n, cows[20010];

bool mycmp(int a, int b){
	int ret = 0;
	for (int i=0; i<5; ++i){
		if (pos[i][a] < pos[i][b]) ret++;
	}
	return ret >= 3;
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	
	for (int np=0; np<5; ++np){
		for (int i=0; i<n; ++i){
			int c; cin >> c;
			pos[np][c] = i;
			cows[i] = c;
		}
	}
	sort(cows, cows + n, mycmp);
	for (int i=0; i<n; ++i){
		cout << cows[i] << '\n';
	}


	return 0;
}