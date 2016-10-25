#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    long long N, K, cuts = 0, pcs;
    cin >> N >> K;
    for (pcs=1; pcs<K; pcs*=2, cuts++){
        if (pcs >= N){
            cout << cuts;
            return 0;
        }
    }
    cuts+= (N+K-1-pcs)/K;
  //  for (; pcs<N; pcs+=K, cuts++);
    
    cout << cuts;
    
    return 0;
}
