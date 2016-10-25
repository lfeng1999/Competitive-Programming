#include <bits/stdc++.h>

using namespace std;

void solve(int n, int k, string cur){
    if (n == 0){
        cout << cur << '\n';
        return;
    }
    else if (k == 0){
        solve(n-1, k, cur + "0");
        return;
    }
    if (n == k){
        solve(n-1, k-1, cur + "1");
    }
    else{
        solve(n-1, k-1, cur + "1");
        solve(n-1,k, cur + "0");
    }
}

int main()
{
//    freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int QQ;
    cin >> QQ;
    while (QQ--){
    int n, k;
        cin >> n >> k;
        cout << "The bit patterns are\n";
        solve(n, k, "");
        cout << '\n';
    }


    return 0;
}
