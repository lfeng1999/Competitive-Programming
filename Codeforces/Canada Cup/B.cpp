#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
	//freopen("CF.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
    ll row;
    char pos;
    cin >> row >> pos;

    if (row%4 == 0 || row % 4 == 3) row -=2;

    ll ans = row - 1;

    ans += ((ll)(row/2))*6;

    if (pos == 'f') ans+=1;
    if (pos == 'e') ans+=2;
    if (pos == 'd') ans+=3;
    if (pos == 'a') ans+=4;
    if (pos == 'b') ans+=5;
    if (pos == 'c') ans+=6;
    cout << ans;

	return 0;
}