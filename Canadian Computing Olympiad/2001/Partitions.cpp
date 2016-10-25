#include <bits/stdc++.h>

using namespace std;

int perms[110][110];

int setup(int k, int a){
    int &ans = perms[k][a];
    if (perms[k][a] != 1e9) return perms[k][a];
    else if (k == 0 || a == 1) return ans = 1;
    ans = 0;
    for (; a > 0; a--){
        if (a > k) continue;
        ans += setup(k-a, a);
    }
    return ans;
}

void solve(int k, int a){
    if (k == 0) return;
    int b = lower_bound(perms[k], perms[k] + 105, a) - perms[k];
    cout << b;
    if (k > b) cout << ",";
    solve(k - b, a - perms[k][b-1]);
}

int main()
{
//    freopen("CCO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<110; ++i)
        for (int j=1; j<110; ++j)
            perms[i][j] = 1e9;
    for (int i=105; i>=0; --i)
        for (int j=i; j>=0; --j)
            setup(i,j);
    int qq;
    cin >> qq;
    while (qq--){
        int k, a;
        cin >> k >> a;
        if (a > perms[k][min(k,a)]){
            cout << "Too big" << "\n";
        }
        else{
            cout << "(";
            solve(k, a);
            cout << ")\n";
        }
    }
    return 0;
}
