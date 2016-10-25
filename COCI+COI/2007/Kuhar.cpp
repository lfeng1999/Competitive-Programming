#include <bits/stdc++.h>

using namespace std;

int N, M, serv[110], kitch[110], smallsz[110], smallp[110], largesz[110], largep[110];

bool valid(int serv_needed){

    int cash = M;

    for (int i = 0; i < N; ++i){
        int ing_needed = serv_needed*serv[i] - kitch[i];

        int cost = 1e9;

        for (int j = 0; j <= ing_needed / smallsz[i] + 1; j++){
            int ing_left = ing_needed - smallsz[i]*j;
            int  k = (ing_left + largesz[i] - 1)/largesz[i];
            cost = min(cost, j*smallp[i] + k*largep[i]);
        }

        cash -= cost;
        if (cash < 0) return false;
    }
    return true;
}

int main()
{
    //freopen("COCI.txt", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i=0; i<N; ++i){
        cin >> serv[i] >> kitch[i] >> smallsz[i] >> smallp[i] >> largesz[i] >> largep[i];
    }
    int L = 0, R = 1000000;
    while (L < R){
        int mid = (L+R)/2 + 1;
        if (valid(mid))
            L = mid;
        else
            R = mid - 1;
    }
    printf("%d\n", L);
    return 0;
}
