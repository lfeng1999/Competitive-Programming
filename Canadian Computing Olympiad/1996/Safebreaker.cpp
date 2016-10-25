#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("CCO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int QQ;
    cin >> QQ;
    while (QQ--){
        int N;
        cin >> N;
        vector<pair<string,string>> V;
        for (int i=0; i<N; ++i){
            string a, b;
            cin >> a >> b;
            V.push_back(make_pair(a,b));
        }
        int tot=0;
        string ans;
        for (int a=0; a<=9; ++a){
            for (int b=0; b<=9;++b){
                for (int c=0; c<=9; ++c){
                    for (int d=0; d<=9; ++d){
                        bool flag = true;
                        int stuff[10]; memset(stuff, 0, sizeof(stuff));
                        stuff[a]++;
                        stuff[b]++;
                        stuff[c]++;
                        stuff[d]++;
                        for (int i=0; i<N; ++i){
                            string S = V[i].first, cnt = V[i].second;
                            int same = 0;
                            if (S[0] == a+'0') same++;
                            if (S[1] == b+'0') same++;
                            if (S[2] == c+'0') same++;
                            if (S[3] == d+'0') same++;
                            if (same+'0' != cnt[0]){flag = false; break;}
                            int stuff2[10]; memset(stuff2, 0, sizeof(stuff2));
                            stuff2[S[0]-'0']++;
                            stuff2[S[1]-'0']++;
                            stuff2[S[2]-'0']++;
                            stuff2[S[3]-'0']++;

                            int nsame = 0;
                            for (int j=0; j<10; ++j){
                                nsame+=min(stuff2[j], stuff[j]);
                            }
                            if (nsame-same+'0' != cnt[2]){
                                flag = false;
                                break;
                            }
                        }
                        if (flag){
                            tot++;
                            ans += a+'0';
                            ans += b+'0';
                            ans += c+'0';
                            ans += d+'0';

                        }
                    }
                }
            }
        }
        if (tot > 1){
            cout << "indeterminate\n";
        }
        else if (tot == 0){
            cout << "impossible\n";
        }
        else{
            cout << ans << "\n";
        }
    }
    return 0;
}
