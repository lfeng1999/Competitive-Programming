#include <bits/stdc++.h>

using namespace std;

int arr[3000010], cnt[3000010];

int main()
{
//    freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0);
    set<int> S;
    int N, K;
    cin >> N >> K;
    long long ans = 0;
    int set_size = 0;
    int cur = 0;
    for (int i=0; i<N; ++i){
        int k;
        cin >> k;
        if (cnt[k] == 0){
            S.insert(k);
        }
        arr[i] = k; cnt[k]++;
        set_size++;
        while (*(--S.end()) - *S.begin() > K){
            int p = arr[cur++]; cnt[p]--;
            if (cnt[p] == 0){
                S.erase(p);
            }
            set_size--;
        }
        ans+=set_size;
    }
    cout << ans;

    return 0;
}