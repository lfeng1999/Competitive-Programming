#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    bool flag = false;
    for (int i=1; i<=10; ++i){
        if (a <= i && i <= b){
            if (c <= i && i <= d){
                flag = true;
            }
        }
    }
    if (flag && b!=c && a!=d) cout << "YES";
    else cout << "NO";
    return 0;
}
