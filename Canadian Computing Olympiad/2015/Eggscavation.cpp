#include <bits/stdc++.h>

using namespace std;

int N, K, grid[2510][2510], bit[2510][2510], shells;

vector<int> order[2510];
bool seg_zero[2510][8200];

void update(int *arr, int x, int val){
    for (; x <= N+5; x += x&(-x))
        arr[x] += val;
}
int query(int *arr, int x){
    int tot = 0;
    for (; x > 0; x -= x&(-x))
        tot += arr[x];
    return tot;
}

struct Rect{
    int x1, y1, x2, y2;
    Rect(int x1, int y1, int x2, int y2) :
        x1(x1), y1(y1), x2(x2), y2(y2){}
};

void fill_rect(int x1, int y1, int x2, int y2, int val){
    grid[x1][y1] += val;
    grid[x1][y2+1] -= val;
    grid[x2+1][y1] -= val;
    grid[x2+1][y2+1] += val;
}

void setup(vector<Rect> &V){
    for (int i=0; i < V.size(); ++i){
        fill_rect(V[i].x1, V[i].y1, V[i].x2, V[i].y2, 1);
    }
    for (int i=0; i<V.size(); ++i){
        for (int j = i+1; j<V.size(); ++j){
            int x1 = max(V[i].x1, V[j].x1), x2 = min(V[i].x2, V[j].x2),
                y1 = max(V[i].y1, V[j].y1), y2 = min(V[i].y2, V[j].y2);
            if (x1 > x2 || y1 > y2) continue;
            fill_rect(x1, y1, x2, y2, -1);
        }
    }
    for (int i=0; i<V.size(); ++i){
        for (int j = i+1; j<V.size(); ++j){
            for (int k = j+1; k<V.size(); ++k){
                int x1 = max(V[k].x1, max(V[i].x1, V[j].x1)), x2 = min(V[k].x2, min(V[i].x2, V[j].x2)),
                    y1 = max(V[k].y1, max(V[i].y1, V[j].y1)), y2 = min(V[k].y2, min(V[i].y2, V[j].y2));
                if (x1 > x2 || y1 > y2) continue;
                fill_rect(x1, y1, x2, y2, 1);

            }
        }
    }
    if (V.size() != 4) return;
    int x1 = max(V[0].x1, max(V[1].x1, max(V[2].x1, V[3].x1))),
        x2 = min(V[0].x2, min(V[1].x2, min(V[2].x2, V[3].x2))),
        y1 = max(V[0].y1, max(V[1].y1, max(V[2].y1, V[3].y1))),
        y2 = min(V[0].y2, min(V[1].y2, min(V[2].y2, V[3].y2)));
    if (x1 > x2 || y1 > y2) return;
    fill_rect(x1, y1, x2, y2, -1);
}

void update_seg(bool *seg, int v, int L, int R, int LL, int RR, int r){
    if (seg[v] == true) return;

    if (LL <= L && R <= RR) seg[v] = true;

    if (L == R){
        update(bit[r], grid[r][L], -1);
        update(bit[r], 1, 1);
        return;
    }
    if ((L+R)/2 >= LL)
        update_seg(seg, v*2, L, (L+R)/2, LL, RR, r);
    if ((L+R)/2+1 <= RR)
        update_seg(seg, v*2 + 1, (L+R)/2+1, R, LL, RR, r);
}



int main()
{
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N >> K >> shells;

    while (shells--){
        int S;
        cin >> S;
        vector<Rect> V;

        for (int i=0; i<S; ++i){
            int x, y;
            cin >> x >> y;
            int x1 = max(1, x - K + 1), x2 = min(N - K + 1, x);
            int y1 = max(1, y - K + 1), y2 = min(N - K + 1, y);
            V.push_back(Rect(x1, y1, x2, y2));
        }
        setup(V);
    }
    for (int j=1; j<=N-K+1; ++j){
        for (int i=1; i<=N-K+1; ++i){
            grid[i][j] += grid[i-1][j];
        }
    }
    for (int i=1; i<=N-K+1; ++i){
        map<int,int> M;
        M[0];
        for (int j=1; j<=N-K+1; ++j){
            grid[i][j] += grid[i][j-1];
            M[grid[i][j]];
        }
        int maxi = 0;
        for (map<int,int>::iterator it = M.begin(); it != M.end(); it++){
            maxi++;
            order[i].push_back(it->first);
            M[it->first] = maxi;
        }
        for (int j=1; j<=N-K+1; ++j){
            grid[i][j] = M[grid[i][j]];
            update(bit[i], grid[i][j], 1);
        }
    }
    double totarea = (N-K+1)*(N-K+1);
    int QQ; int outputcnt = 0;
    cin >> QQ;
    while (QQ--){
       int C;
       cin >> C;
       if (C == 1){
            int x, y;
            cin >> x >> y;
            int x1 = max(1, x - K + 1), y1 = max(1, y - K +1);
            int x2 = min(x, N - K + 1), y2 = min(y, N - K + 1);
            for (int r = x1; r <= x2; r++){
                update_seg(seg_zero[r], 1, 1, N - K + 1, y1, y2, r);
            }
       }
       else if (C == 2){
            int V; cin >> V;
            double tot = 0;
            for (int i=1; i<=N-K+1; ++i){
                int pos = lower_bound(order[i].begin(), order[i].end(), V) - order[i].begin();

                tot += N - K + 1 - query(bit[i], pos);
            }
            printf("%.6f\n", tot/totarea);
       }
    }

    return 0;
}
