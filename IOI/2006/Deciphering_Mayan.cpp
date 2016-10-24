#include <bits/stdc++.h>

using namespace std;

int freq[257];
char mayan[3000001];
int same = 0, ans = 0;

int main()
{
    //freopen("DTMW.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int a,b;
    cin >> a >> b;
    for (int i=0; i!=a; ++i){
        char x;
        cin >> x;
        freq[x]++;
    }
    for (int i=0; i!=257; ++i){
        if (freq[i] == 0){
            same++;
        }
    }
    for (int i=0; i!=b; ++i){
        cin >> mayan[i];
        if (freq[mayan[i]] == 0){
            same--;
        }
        freq[mayan[i]]--;
        if (freq[mayan[i]] == 0){
            same++;
        }
        if (i >= a){
            if (freq[mayan[i-a]] == 0){
                same--;
            }
            freq[mayan[i-a]]++;
            if (freq[mayan[i-a]] == 0){
                same++;
            }
        }
        if (same == 257){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
