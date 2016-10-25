#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
int nweak, nsmall, T;
int weak_robot[50010];
int small_robot[50010];
vector<pair<int,int>> toys; //weight, size

bool valid(int tim){
    priority_queue<int> Q;

    int t_cnt = 0;
    for (int i=0; i<nweak; ++i){
        while (t_cnt != T && toys[t_cnt].first < weak_robot[i]){
            Q.push(toys[t_cnt].second);
            t_cnt++;
        }
        for (int j=0; j<tim && !Q.empty(); ++j){
            Q.pop();
        }
    }
    while (t_cnt != T){
        Q.push(toys[t_cnt].second);
        t_cnt++;
    }
    for (int i = nsmall - 1; i >= 0 && !Q.empty(); --i){
        for (int j=0; j<tim && !Q.empty(); ++j){
            if (small_robot[i] > Q.top()) Q.pop();
            else break;
        }
    }
    return Q.empty();
}


int main()
{
//    freopen("IOI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> nweak >> nsmall >> T;
    for (int i=0; i<nweak; ++i){
        cin >> weak_robot[i];
    }
    for (int i=0; i<nsmall; ++i){
        cin >> small_robot[i];
    }
    sort(weak_robot, weak_robot + nweak);
    sort(small_robot, small_robot + nsmall);
    for (int i=0; i<T; ++i){
        int w, s;
        cin >> w >> s;
        toys.push_back(make_pair(w, s));
    }
    sort(toys.begin(), toys.end());

    int L = -1, R = 1e9 + 1;
    while (L < R){
        int mid = (L+R)/2;
        if (valid(mid)) R = mid;
        else L = mid + 1;
    }
    if (L != 1e9 + 1)
        cout << L << endl;
    else
        cout << -1 << endl;
    return 0;
}
