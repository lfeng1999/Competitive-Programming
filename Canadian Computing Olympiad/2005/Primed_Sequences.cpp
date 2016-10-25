#include <bits/stdc++.h>

using namespace std;

int psum[10010], seq[10010];

bool works(int N){
    if (N%2 == 0) return false;
    for (int i=3; i<=sqrt(N); i+=2){
        if (N%i == 0) return false;
    }
    return true;
}

int main()
{
//    freopen("CCO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int QQ;
    cin >> QQ;
    while (QQ--){
        int N;
        cin >> N;
        for (int i=1; i<=N; ++i){
            cin >> seq[i];
            psum[i] = seq[i] + psum[i-1];
        }
        int best_len = -1, start = -1;
        for (int len = N; len > 1; len--){
            for (int i=0; i<=N-len; i++){
                if (works(psum[i+len] - psum[i])){
                    start = i;
                    best_len = len;
                    break;
                }
            }
        }
        if (best_len == -1){
            cout << "This sequence is anti-primed.\n";
        }
        else{
            cout << "Shortest primed subsequence is length " << best_len << ": ";
            for (int i=start+1; i<=start+best_len; i++){
                cout << seq[i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
