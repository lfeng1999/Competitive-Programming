#include <bits/stdc++.h>

using namespace std;

int N, pos[1000010];

int main()
{
    //freopen("IOI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    vector<int> V, V2;

    cin >> N;
    for (int i=0; i < N; ++i){
        int v; cin >> v;
        pos[v-1] = i;
    }

    for (int i=0; i < N; ++i){
        int dif = pos[i] - i;
        if (dif < 0) dif += N;

        V.push_back(dif);
        if (dif != 0)
            V2.push_back(N - dif);
        else
            V2.push_back(dif);
    }
    sort(V.begin(), V.end());
    sort(V2.begin(), V2.end());
    V.push_back(V[0] + N);
    V2.push_back(V2[0] + N);

    int best = 0;
    for (int i=0; i < N; ++i){
        best = max(best, V[i+1] - V[i]);
        best = max(best, V2[i+1] - V2[i]);
    }

    cout << (N - best + 1) / 2;



    return 0;
}
