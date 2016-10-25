#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;

    vector<pair<int,int>> V;

    for (int i=1; i<=N; ++i){
        bitset<31> bits = i;
        for (int j=0; j<15; ++j){
            int t = bits[j];
            bits[j] = bits[30-j];
            bits[30-j] = t;
        }
        V.push_back(make_pair(bits.to_ulong(), i));
    }
    sort(V.begin(), V.end());

    for (int i=0; i<N; ++i){
        printf("%d\n", V[i].second);
    }


    return 0;
}
