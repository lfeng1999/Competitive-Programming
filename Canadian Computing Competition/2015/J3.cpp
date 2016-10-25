#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    string w, nw;
    cin >> w;
    char vow[5] = {'a','e','i','o','u'};
    for (int i=0; i<w.length(); ++i){
        nw+=w[i];
        if (find(vow, vow+5, w[i])!=vow+5) continue;
        int nd = 1e6, v;
        for (int j=0; j<5; ++j){
            if (abs(w[i]-vow[j]) < nd){
                nd = abs(w[i]-vow[j]);
                v=j;
            }
        }
        nw+=vow[v];
        for (int j=1; j<100; ++j){
            char nc = w[i]+j;
            if (find(vow,vow+5,nc)!=vow+5) continue;
            if (nc > 'z') nw+='z';
            else nw+=nc;
            break;
        }
    }
    cout << nw;
    return 0;
}
