#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

struct plant{
    int x, y, flies, best, how;
    int orig_pos;

    bool operator < (const plant &a) const{
        if (x != a.x) return x < a.x;

        return y < a.y;
    }
} plants[100010];

int N, K, best_x[100010], best_y[100010], sorted[100010];

int main()
{
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;

    fill(best_x, best_x+N, N);
    fill(best_y, best_y+N, N);

    for (int i=0; i<N; ++i){
        cin >> plants[i].x >> plants[i].y >> plants[i].flies;
        plants[i].orig_pos = i;
    }
    sort(plants, plants+N);
    for (int i=0; i<N; ++i){
        sorted[plants[i].orig_pos] = i;
    }

    plants[N].best = -1e9;

    best_x[plants[sorted[0]].x] = sorted[0];
    best_y[plants[sorted[0]].y] = sorted[0];
    plants[sorted[0]].best = plants[sorted[0]].flies;

    for (int i = sorted[0] + 1; i<=sorted[N-1]; ++i){
        int bx = best_x[plants[i].x],by = best_y[plants[i].y];
        if (plants[bx].best >= plants[by].best){
            if (plants[bx].best < K) continue;

            plants[i].best = plants[bx].best + plants[i].flies - K;
            plants[i].how = bx;
        }
        else{
            if (plants[by].best < K) continue;

            plants[i].best = plants[by].best + plants[i].flies - K;
            plants[i].how = by;
        }

        if (plants[i].best > plants[bx].best) best_x[plants[i].x] = i;

        if (plants[i].best > plants[by].best) best_y[plants[i].y] = i;
    }


    cout << plants[sorted[N-1]].best << endl;

    stack<pair<int,int>> points;

    int i = sorted[N-1], sz = 1;
    while (i != sorted[0]){
        points.push(make_pair(plants[i].x, plants[i].y));
        i = plants[i].how;
        sz++;
    }
    cout << sz << endl;
    cout << plants[i].x << " " << plants[i].y << endl;
    while (!points.empty()){
        cout << points.top().first << " " << points.top().second << endl;
        points.pop();
    }


    return 0;
}
