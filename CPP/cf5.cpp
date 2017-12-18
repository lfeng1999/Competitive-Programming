#include <bits/stdc++.h>

using namespace std;

int N, s[1000010], npile[61], pileleft;
bool winner[1000010][2];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	int odd = 0;
	for (int i=1; i<=N; ++i){
		cin >> s[i];
		if (s[i] != 1 && s[i] != 2){
			pileleft++;
		}
		else{
			odd++;
		}
	}
	odd%=2;
	int player = 0;
	winner[0][0] = false;
	winner[0][1] = true;
	winner[1][0] = true;
	winner[1][1] = true;
	winner[2][0] = false;
	for (int i=2; i<=N; ++i){
		if (winner[i-1][0] == false || winner[i-1][1] == false)
			winner[i][0] = true;
		if (winner[i][0] == false || winner[i-1][0] == false || winner[i-1][1] == false)
			winner[i][1] = true;
	}
	if (winner[pileleft][odd]){
		cout << "NO";
	}
	else{
		cout << "YES";
	}
	return 0;
}