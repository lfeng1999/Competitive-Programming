#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
priority_queue<pair<ll, ll>> teams;
int N;
priority_queue<ll, vector<ll>, greater<ll>> balloon_need;

int main(){
//    freopen("CF.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    ll curballoon, curweight;
    cin >> curballoon >> curweight;

    for (int i=1; i<N; ++i){
        ll b, w;
        cin >> b >> w;
        if (b > curballoon)
            balloon_need.push(w - b + 1);
        else
            teams.push(make_pair(b, w));
    }
    int best = balloon_need.size() + 1;
    int idx = 0;
    
    while (!balloon_need.empty() && curballoon >= balloon_need.top()){
        curballoon -= balloon_need.top();
        balloon_need.pop();

        while (!teams.empty() && curballoon < teams.top().first){
            balloon_need.push(teams.top().second - teams.top().first + 1);
            teams.pop();
        }
        best = min(best, (int)balloon_need.size()+1);
    }
    cout << best;

    return 0;
}