#include <bits/stdc++.h>

using namespace std;

pair<int,int> vase[2001];

int main()
{
    cin.sync_with_stdio(0);cin.tie(0);
    int N;
    cin >> N;
    for (int i=1; i <= N; ++i){
        int mbit = 10, x = 0, j = i;
        while (j > 0){
            if (j & 1){
                x+= 1 << mbit;
            }
            j >>= 1;
            mbit--;
        }
        vase[i-1] = make_pair(x,i);
    }
    sort(vase, vase + N);
    for (int i=0; i!=N; ++i){
        printf("%d\n",vase[i].second);
    }
    return 0;
}
