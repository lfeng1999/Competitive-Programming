#include <bits/stdc++.h>

using namespace std;

set<string> pos;

int main()
{
    string a;
    cin >> a;
    for (char x = 'a'; x<='z'; ++x){
        for (int i=0; i<=a.length(); ++i){
            pos.insert(a.substr(0,i) + x + a.substr(i,a.length()));
        }
    }
    cout << pos.size();

    return 0;
}