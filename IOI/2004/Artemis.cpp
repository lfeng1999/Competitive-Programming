#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20001;
int N, mT = MAXN, T, p1, p2, minT = MAXN, loY[MAXN], sq[MAXN];

struct point
{
    int x, y, id;
    bool operator < (const point &a) const{
        return x < a.x;
    }
} P[MAXN];

int main()
{
    //freopen("artemis-1.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> T;
    //cout << N << " " << T << endl;
    for (int i=0; i!=N; ++i){
        cin >> P[i].x >> P[i].y;
        P[i].id = i+1;
    }
    sort(P, P+N);
    for (int i=0; i!=N; ++i){
        loY[i] = i;
        for (int j=0; j!=i; ++j){
            if (P[j].y > P[i].y){
                loY[i]--;
                loY[j]++;
            }
        }
        sq[i] = loY[i];
        int lim = i - T + 2, cant = 0, cnt = 0;
        for (int j=0; j<=lim; ++j){
            int val = abs(sq[i] - loY[j] - cnt + sq[j]) + 1;
            if (val >= T && val < mT){
                mT = val;
                p1 = P[j].id;
                p2 = P[i].id;
            }
            if (P[j].y < P[i].y){
                cnt++;
            }
        }
    }
    cout << p1 << " " << p2;

    return 0;
}
