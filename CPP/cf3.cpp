#include <bits/stdc++.h>

using namespace std;

int n, k, x, arr[3][100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k >> x;
	for (int i=1; i<=n; ++i){
		cin >> arr[0][i];
	}
	sort(arr[0]+1, arr[0]+1+n);
	for (int j=1; j<=n; j++){
		if (j%2 == 1)
			arr[1][j] = arr[0][j]^x;
		else
			arr[1][j] = arr[0][j];
	}
	sort(arr[1]+1, arr[1]+1+n);
	bool is_same = true;
	for (int j=1;j<=n; ++j){
		if (arr[0][j] != arr[1][j]){
			is_same = false;
		}
	}
	if (is_same || k == 0){		
		cout << arr[0][n] << " " << arr[0][1] << '\n';
		return 0;
	}
	if (k == 1){
		cout << arr[1][n] << " " << arr[1][1] << '\n';
		return 0;
	}
	for (int i=2; i<=k; ++i){
		for (int j=1; j<=n; j++){
			if (j%2 == 1)
				arr[2][j] = arr[1][j]^x;
			else
				arr[2][j] = arr[1][j];
		}
		sort(arr[2], arr[2]+1+n);
		bool flag = true;
		for (int j=1; j<=n; ++j){
			if (arr[0][j] != arr[2][j]){
				flag = false;
			}
		}
		if (flag){
			if ((k-i)%2 == 1){
				cout << arr[1][n] << " " << arr[1][1] << '\n';
			}
			else{
				cout << arr[2][n] << " " << arr[2][1] << '\n';
			}
			return 0;
		}
		for (int j=0; j<=1; ++j){
			for (int p=1; p<=n; ++p){
				arr[j][p] = arr[j+1][p];
			}
		}
	}
	cout << arr[1][n] << " " << arr[1][1] << '\n';


	return 0;
}