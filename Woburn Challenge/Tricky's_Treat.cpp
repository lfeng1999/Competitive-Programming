#include <bits/stdc++.h>

using namespace std;

pair<int,int> houses[100010];

int main(){
    //freopen("WC.txt","r",stdin);

    int N, M, T;
    cin >> N >> M >> T;

    for (int i=0; i<N; ++i){
        cin >> houses[i].first >> houses[i].second;
    }
    sort(houses, houses+N);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    int best_candy = 0, cur_candy = 0;

    Q.push(make_pair(houses[0].second, houses[0].first));
    if (houses[0].first*2 + T <= M){
        cur_candy = Q.top().first;
    }

    for (int i=1; i<N; ++i){
        Q.push(make_pair(houses[i].second, houses[i].first));

        cur_candy += houses[i].second;

        int cur_time = Q.size()*T + houses[i].first*2;

        while (!Q.empty() && cur_time > M){
            cur_time -= T;
            cur_candy -= Q.top().first;
            Q.pop();
        }


        best_candy = max(best_candy, cur_candy);

    }
    cout << best_candy;



    return 0;
}
