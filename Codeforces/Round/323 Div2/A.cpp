#include <bits/stdc++.h>

using namespace std;

bool v[51], h[51];

int main()
{
 //   freopen("IOI.txt","r",stdin);
    int N;
    memset(h,false,sizeof(h));
    memset(v,false,sizeof(v));
    cin >> N;
    for (int i=0; i!=N*N; ++i){
        int a,b;
        cin >> a >> b;
        if (!h[a] && !v[b]){
            cout << i+1 << " ";
            h[a] = v[b] = true;
        }
    }
    return 0;
}