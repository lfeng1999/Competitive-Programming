#include <bits/stdc++.h>

using namespace std;

int N, M;

vector<int> men;
vector<pair<int,int>> doors;

int main()
{
    //freopen("WoburnChallenge.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;


    for (int i=0; i<N; ++i){
        int v;
        cin >> v;
        men.push_back(v);
    }
    for (int i = 0; i < M; ++i){
        int v; cin >> v;
        doors.push_back(make_pair(v, i));
    }
    doors.push_back(make_pair(2e9, M));
    sort(men.begin(), men.end());
    sort(doors.begin(), doors.end());

    int curdoor = 1, i = 0, j = 0;

    while (curdoor <= M){

        while (doors[j].second < curdoor){
            j++;
        }

//            while (i != men.size() && men[i] < doors[j].first){
//                i++;
//            }

        cout << lower_bound(men.begin(), men.end(), doors[j].first) - men.begin() << "\n";
        curdoor++;
    }



    return 0;
}
