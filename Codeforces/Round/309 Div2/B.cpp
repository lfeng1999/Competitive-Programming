#include <bits/stdc++.h>

using namespace std;

map<string,int> cnt;

int main()
{
    int n;
    cin >> n;
    for (int i=0; i!=n; ++i){
        string a;
        cin >> a;
        cnt[a]++;
    }
    int maxn = 0;
    for (auto pp: cnt){
        maxn = max(maxn,pp.second);
    }
    cout << maxn;
    return 0;
}