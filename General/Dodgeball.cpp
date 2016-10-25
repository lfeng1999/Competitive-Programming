#include <bits/stdc++.h>

using namespace std;


const long long MOD = 1e9 + 7;
#define endl '\n'

int main(){
    //freopen("testdata.txt","r",stdin);
    int nPeople; cin >> nPeople;
    int first_letter = -100, nCount = 0;
    long long ans = 0;

    while (nPeople--){
        string name; cin >> name;

        int cur_letter;
        if (name[0] > 'A'){
            cur_letter = name[0] - 'A';
        }
        else{
            cur_letter = name[0] - 'a';
        }

        if (cur_letter == first_letter){
            nCount++;
        }
        else{
            ans += nCount*(nCount+1)/2;
            ans %= MOD;
            nCount = 1;
            first_letter = cur_letter;
        }
    }
    ans += nCount*(nCount+1)/2;
    ans %= MOD;

    cout << ans;


    return 0;
}