#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int,int>> points;

vector<int> Xs[100010], Ys[100010];

ll works(int i){
    int x = points[i].first, y = points[i].second;
    ll xless = lower_bound(Xs[x].begin(), Xs[x].end(), y) - Xs[x].begin();
    ll xmore = Xs[x].size() - xless - 1;
    ll yless = lower_bound(Ys[y].begin(), Ys[y].end(), x) - Ys[y].begin();
    ll ymore = Ys[y].size() - yless - 1;
    return xless*xmore*yless*ymore;

}

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    for (int i=0; i<N; ++i){
        int x, y;
        cin >> x >> y;
        points.push_back(make_pair(x,y));
    }
    sort(points.begin(), points.end());
    int cnt = 0, cur = -1e9;
    for (int i=0; i<N; ++i){
        if (cur != points[i].first)
            cnt++;
        cur = points[i].first;
        points[i].first =  cnt;
    }
    sort(points.begin(), points.end(), [](pair<int,int> a, pair<int,int> b){
         return make_pair(a.second, a.first) < make_pair(b.second, b.first);
    });
    cnt = 0, cur = -1e9;
    for (int i=0; i<N; ++i){
        if (cur != points[i].second)
            cnt++;
        cur = points[i].second;
        points[i].second =  cnt;
    }

    sort(points.begin(), points.end());

    for (int i=0; i<N; ++i){
        Xs[points[i].first].push_back(points[i].second);
    }
    sort(points.begin(), points.end(), [](pair<int,int> a, pair<int,int> b){
         return make_pair(a.second, a.first) < make_pair(b.second, b.first);
    });
    for (int i=0; i<N; ++i){
        Ys[points[i].second].push_back(points[i].first);
    }

    sort(points.begin(), points.end());
    ll valid = 0;
    for (int i=0; i<N; ++i){
            valid+=works(i);
    }



    cout << valid*2;
    return 0;
}