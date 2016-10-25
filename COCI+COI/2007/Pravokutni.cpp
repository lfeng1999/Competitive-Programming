#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int N;
vector<pii> points;

bool cmp(pii a, pii b){
    return 1ll * a.first * b.second < 1ll * a.second * b.first;
}

int solve(int idx){
    vector<pii> lo, hi, V;
    int xzero = 0;

    for (int i=0; i<N; ++i){
        if (i != idx){

            if (points[idx].first < points[i].first){
                lo.push_back(make_pair(points[idx].first - points[i].first, points[idx].second - points[i].second));
            }
            else if (points[idx].first > points[i].first){
                hi.push_back(make_pair(points[idx].first - points[i].first, points[idx].second - points[i].second));
            }
            else{
                xzero++;
            }
            V.push_back(make_pair(points[idx].first - points[i].first, points[idx].second - points[i].second));
        }
    }
    sort(lo.begin(), lo.end(), cmp);
    sort(hi.begin(), hi.end(), cmp);

    int ans = 0;
    for (int i=0; i<V.size(); ++i){
        if (V[i].second == 0){
            ans += xzero;
            continue;
        }
        if (-V[i].second > 0){
            ans +=  upper_bound(hi.begin(), hi.end(), make_pair(-V[i].second, V[i].first), cmp) -
                    lower_bound(hi.begin(), hi.end(), make_pair(-V[i].second, V[i].first), cmp);
        }
        else if (-V[i].second < 0){
            ans +=  upper_bound(lo.begin(), lo.end(), make_pair(-V[i].second, V[i].first), cmp) -
                    lower_bound(lo.begin(), lo.end(), make_pair(-V[i].second, V[i].first), cmp);
        }
        if (V[i].second > 0){
            ans +=  upper_bound(hi.begin(), hi.end(), make_pair(V[i].second, -V[i].first), cmp) -
                    lower_bound(hi.begin(), hi.end(), make_pair(V[i].second, -V[i].first), cmp);
        }
        else if (V[i].second < 0){
            ans +=  upper_bound(lo.begin(), lo.end(), make_pair(V[i].second, -V[i].first), cmp) -
                    lower_bound(lo.begin(), lo.end(), make_pair(V[i].second, -V[i].first), cmp);
        }
    }
    return ans/2;
}

int main()
{
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=0; i<N; ++i){
        int x, y; cin >> x >> y;
        points.push_back(make_pair(x, y));
    }
    int ans = 0;
    for (int i=0; i<N; ++i){
        ans += solve(i);
    }
    cout << ans;
    return 0;
}
