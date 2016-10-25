#include <bits/stdc++.h>

using namespace std;

struct Node{
    int x1, y1, x2, y2, id, p;
} seg[200010];

struct Window{
    int x1, y1, x2, y2, id, p;
    bool operator < (Window &w){
        return  make_pair(x1, x2) < make_pair(w.x1, w.x2);
    }
} windows[50010];

void build_tree(int v, int L, int R){
    if (L == R){
        seg[v].x1 = windows[L].x1;
        seg[v].y1 = windows[L].y1;
        seg[v].x2 = windows[L].x2;
        seg[v].y2 = windows[L].y2;
        seg[v].id = windows[L].id;
        seg[v].p = windows[L].p;
    }
    else{
        build_tree(v*2, L, (L+R)/2);
        build_tree(v*2+1, (L+R)/2 +1, R);

        seg[v].x1 = min(seg[v*2].x1, seg[v*2+1].x1);
        seg[v].y1 = min(seg[v*2].y1, seg[v*2+1].y1);
        seg[v].x2 = max(seg[v*2].x2, seg[v*2+1].x2);
        seg[v].y2 = max(seg[v*2].y2, seg[v*2+1].y2);
        seg[v].id = 0;
        seg[v].p = max(seg[v*2].p, seg[v*2+1].p);
    }
}

int C, R, best, bestid;

void update(int v, int L, int R, int x, int y, int val){
    if (seg[v].p < best)
        return;
    if (seg[v].x1 <= x && x <= seg[v].x2 && seg[v].y1 <= y && y <= seg[v].y2){
        if (L == R)
            seg[v].p = val;
        else{
            update(v*2, L, (L+R)/2, x, y, val);
            update(v*2 + 1, (L+R)/2 + 1, R, x, y, val);

            seg[v].p = max(seg[v*2].p, seg[v*2+1].p);
        }
    }
}

void query(int v, int L, int R, int x, int y){
    if (seg[v].p < best)
        return;
    if (seg[v].x1 <= x && x <= seg[v].x2 && seg[v].y1 <= y && y <= seg[v].y2){
        if (L == R){
            best = seg[v].p;
            bestid = seg[v].id;
        }
        else{
            query(v*2, L, (L+R)/2, x, y);
            query(v*2+1, (L+R)/2 + 1, R, x , y);
        }
    }
}

int main()
{
    //freopen("CCO.txt", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> C >> R;
    int N;
    cin >> N;
    for (int i=0; i<N; ++i){
        cin >> windows[i].x1 >> windows[i].y1 >> windows[i].x2 >> windows[i].y2;
        swap(windows[i].y1, windows[i].y2);
        windows[i].id = i + 1;
        windows[i].p = i + 1;
    }
    sort(windows, windows + N);

    build_tree(1, 0, N - 1);

    int QQ;
    cin >> QQ;
    for (int qq = 1; qq <= QQ; ++qq){
        int x, y; best = 0, bestid = 0;
        cin >> x >> y;
        query(1, 0, N - 1, x, y);
        printf("%d\n", bestid);
        update(1, 0, N - 1, x, y, N + qq);
    }


    return 0;
}
