#include <bits/stdc++.h>

using namespace std;

string S1, S2;
int glyph[55], cur[55];
unordered_map<char, int> comp;

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int A, B;
    cin >> A >> B >> S1 >> S2;
    //printf("%d %d %s %s\n", A, B, S1.c_str(), S2.c_str());
    int cnt = 1;
    for (char a = 'a'; a <= 'z'; a++) comp[a] = cnt++;
    for (char a = 'A'; a <= 'Z'; a++) comp[a] = cnt++;

    for (char c : S1){
        glyph[comp[c]]++;
    }

    int notsame = 0;
    for (int i=0; i<55; ++i){
        if (glyph[i] != 0) notsame++;
    }

    int ans = 0;
    for (int i=0; i < S2.length(); ++i){
        char c = S2[i];

        if (cur[comp[c]] == glyph[comp[c]]) notsame++;
        cur[comp[c]]++;
        if (cur[comp[c]] == glyph[comp[c]]) notsame--;

        if (i >= S1.length()){
            if (cur[comp[S2[i-S1.length()]]] == glyph[comp[S2[i-S1.length()]]])
                notsame++;

            cur[comp[S2[i-S1.length()]]]--;

            if (cur[comp[S2[i-S1.length()]]] == glyph[comp[S2[i-S1.length()]]])
                notsame--;
        }

        if (notsame == 0)
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}
