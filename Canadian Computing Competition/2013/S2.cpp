#include <bits/stdc++.h>

using namespace std;

int cars[100010];

int main()
{
    //freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int W;
    cin >> W;
    int N;
    cin >> N;

    int totweight = 0;
    for (int i=0; i<N; ++i){
        cin >> cars[i];
        totweight += cars[i];

        if (i >= 4) //more than 4
            totweight -= cars[i-4];
        if (totweight > W){ //broke the bridge
            cout << i;
            return 0; //returns 0 in main, finishes program
        }

    }
    cout << N;
    return 0;
}
