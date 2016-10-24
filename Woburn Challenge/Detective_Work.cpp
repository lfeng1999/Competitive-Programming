#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int cnt[510][27], totchar[510];

int main()
{
//    freopen("WC.txt","r",stdin);
    cin.sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    for (int i=0; i<N; ++i){
        string S;
        cin >> S;
        for (int j=0; j<M; ++j){
            if (S[j] == '?') continue;
            cnt[j][S[j] - 'A']++;
            totchar[j]++;
        }
    }

    ll ans = 1;
    int err = 0;

    for (int i=0; i<M; ++i){
        vector<pair<int,int>> V;
        for (int j=0; j<26; ++j){
            if (cnt[i][j]!=0){
                V.push_back(make_pair(cnt[i][j], j));
            }
        }
        if (V.empty()){
            ans*=26;
            ans%=1000;
            continue;
        }
        sort(V.begin(), V.end());
        reverse(V.begin(), V.end());

        int best = V[0].first, nSame = 0;
        for (pair<int,int> mypair : V){
            if (mypair.first == best) nSame++;
            else break;
        }
        err += totchar[i] - V[0].first;
        ans *= nSame;
        ans %= 1000;
    }
    cout << err << " " << ans << "\n";

    return 0;
}
