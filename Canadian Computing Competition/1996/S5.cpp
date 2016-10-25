#include <bits/stdc++.h>

using namespace std;

int X[100010], Y[100010];

int main()
{
//    freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int QQ;
    cin >> QQ;
    while (QQ--){
        int N;
        cin >> N;
        fill_n(Y, N+5, 1e9);
        for (int i=0; i<N; ++i) cin >> X[i];
        for (int i=0; i<N; ++i) cin >> Y[i];

        int ans = 0;
        int j=1;
        for (int i=0; i<N; ++i){
            while (Y[j] >= X[i] && j<N){
                j++;
            }
            ans = max(ans, j-i-1);
        }
        cout << "The maximum distance is " << ans << "\n";
    }
    return 0;
}
