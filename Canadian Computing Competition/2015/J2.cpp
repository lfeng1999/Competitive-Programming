#include <bits/stdc++.h>

using namespace std;

int main()
{
    //cin.sync_with_stdio(0); cin.tie(0);
    string phrase;
    getline(cin, phrase);
    string sm = ":-)", sd = ":-(";
    int c1=0, c2=0;
    while (phrase.find(sm)!=phrase.npos){
        phrase.replace(phrase.find(sm),3," ");c1++;
    }
    while (phrase.find(sd)!=phrase.npos){
        phrase.replace(phrase.find(sd),3," ");c2++;
    }
    if (c1 == 0 && c2 == 0) cout << "none";
    else if (c1 < c2) cout << "sad";
    else if (c1 > c2) cout << "happy";
    else cout << "unsure";
    return 0;
}
