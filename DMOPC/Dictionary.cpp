#include <bits/stdc++.h>

using namespace std;

vector<string> S;

int main()
{
  //  freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    for (int i=0; i<N; ++i){
        string s;
        cin >> s;
        S.push_back(s);
    }
    sort(S.begin(), S.end());
    for (int i=0; i<S.size(); ++i){
        if (i!=0 && S[i][0] != S[i-1][0]) cout << endl;
        else if (i!=0 && S[i][0] == S[i-1][0]) cout << ", ";
        cout << S[i];
    }

    return 0;
}