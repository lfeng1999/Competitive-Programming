#include <bits/stdc++.h>

using namespace std;

int N, D;
string S;

int main(){
    //freopen("WC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N >> D >> S;
    vector<pair<int,int>> rooms;
    for (int i=0; i<S.length(); ++i){
        if (S[i] == '.'){
            int j = i;
            for (; j < S.length() && S[j] == '.'; ++j){
            }
            rooms.push_back(make_pair(i, j-1));
            i = j - 1;
        }
    }
    int cnt = 0;

    for (int i=0; i<rooms.size(); ++i){
     //   cout << i << endl;
        int j;
        for (j = i+1; j < rooms.size(); ++j){
            if (rooms[j].first > rooms[i].second + D){
                break;
            }
        }
        i = j - 1;
   //     cout << i << endl;
        for (j = i+1; j < rooms.size(); ++j){
            if (rooms[j].first > rooms[i].second + D){
                break;
            }
        }
        i = j - 1;
//        cout << i << endl;
        cnt++;
 //       cout << endl;
    }
    cout << cnt;

    return 0;
}
