#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double ERR = 1e-5;

struct Event{
    ll ship, in;
    double tm;
    Event(double tm, ll ship, ll in){
        this->tm = tm;
        this->ship = ship;
        this->in = in;
    }
    bool operator < (const Event &a) const{
        if (tm < a.tm) return true;
        return tm < a.tm;
    }
};
struct Node{
    int L, R, num;
    ll lazy, sum;
}seg[1100000];

bool between (double y, double y1, double y2){
    return (y1-ERR < y && y < y2+ERR);
}

vector<Event> events;

void build_tree(int v, int L, int R){
    seg[v].L = L, seg[v].R = R;
    if (L == R){
        return;
    }
    build_tree(v*2, L, (L+R)/2);
    build_tree(v*2+1, (L+R)/2+1, R);
    return;
}

void update_lazy(int v){
    seg[v].sum += seg[v].lazy*seg[v].num;
    if (seg[v].L == seg[v].R){
        seg[v].lazy = 0;
        return;
    }
    seg[v*2].lazy += seg[v].lazy;
    seg[v*2+1].lazy += seg[v].lazy;
    seg[v].lazy = 0;
    return;
}

void update1(int v, int pos, int val){
    update_lazy(v);
    if (pos < seg[v].L || seg[v].R < pos) return;
    if (pos == seg[v].L && seg[v].L == seg[v].R){
        seg[v].num += val;
        return;
    }
    update1(v*2, pos, val);
    update1(v*2+1, pos, val);
    seg[v].num = seg[v*2].num + seg[v*2+1].num;
    return;
}

void update2(int v, int val){
    seg[v].lazy+=val;
    update_lazy(v);
    return;
}

ll query(int v, int L, int R){
    update_lazy(v);
    if (seg[v].R < L || R < seg[v].L) return 0;
    if (L <= seg[v].L && seg[v].R <= R) return seg[v].sum;
    return query(v*2, L, R) + query(v*2+1, L, R);
}

int main()
{
    //freopen("Woburn.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N, M, x1, y1, x2, y2;
    cin >> N >> M;
    cin >> x1 >> y1 >> x2 >> y2;
    for (int i=1; i<=N; ++i){
        vector<double> cur;
        double sx, sy, dx, dy, nx, ny, m, b, tm;

        cin >> sx >> sy >> dx >> dy;
        if (dx!=0){
            m = (double)dy/dx;
            b = sy - m*sx;

            tm = (x1 - sx)/dx;
            if (between(sy+tm*dy, y1, y2)) cur.push_back(tm);
            tm = (x2 - sx)/dx;
            if (between(sy+tm*dy, y1, y2)) cur.push_back(tm);
        }
        if (dy!=0){
            m = (double)dy/dx;
            b = sy - m*sy;

            tm = (y1 - sy)/dy;
            if (between(sx+tm*dx, x1, x2)) cur.push_back(tm);
            tm = (y2 - sy)/dy;
            if (between(sx+tm*dx, x1, x2)) cur.push_back(tm);
        }
        sort(cur.begin(), cur.end());
        if (cur.size() >= 2){
            events.push_back(Event(cur.front(), i, 1));
            events.push_back(Event(cur.back() + ERR, i, -1));
        }
    }
    sort(events.begin(), events.end());
    build_tree(1, 1, N);
    int j = 0;
    double cur_time = 0;
    for (int qq=0; qq<M; ++qq){
        int A, B, C;
        cin >> A >> B >> C;
        if (A == 1){
            cur_time += B;
            while (j < events.size() && events[j].tm <= cur_time){
                update1(1, events[j].ship, events[j].in);
                j++;
            }
            update2(1, C);
        }
        else{
            printf("%lld\n",query(1, B, C));
//            cout << query(1, B, C) << endl;
        }
    }
    return 0;
}
