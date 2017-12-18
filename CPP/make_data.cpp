#include <bits/stdc++.h>

using namespace std;

int main(){
	freopen("TLE.in","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	// cout << 100000 << '\n';
	printf("%d\n", 100000);
	for (int v=1; v<=99999; ++v){
		// cout << v+1 << " " << 100000 << " " << 100000 << '\n';
		printf("%d %d %d\n", v+1, 100000, 100000);
	}
	fclose(stdout);
	return 0;
}