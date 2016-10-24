#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000001

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0);
    int qq;
    cin >> qq;
    int cnt = 0, min1 = -MAXN, max1 = MAXN;
    for (int i=1; i<= qq; ++i){
        int m;
        cin >> m;
        if (i&1){
            max1 = min(max1, cnt + m);
            cnt+=2*m;
        }
        else{
            min1 = max(min1, cnt - m);
            cnt-=2*m;
        }
    }
    if (max1 >= min1){
        cout << max1 - min1 + 1;
    }
    else{
        cout << 0;
    }
    return 0;
}
