#include <bits/stdc++.h>

using namespace std;

int bit[1050][1050];

int query(int x, int y){
    int tot = 0;
    for (; x > 0; x -= x&(-x))
        for (int yy = y; yy > 0; yy -= yy&(-yy))
            tot += bit[x][yy];
    return tot;
}

void update(int x, int y, int val){
    for (; x < 1050; x += x&(-x))
        for (int yy = y; yy < 1050; yy += yy&(-yy))
            bit[x][yy] += val;
}

int get_sum(int x1, int y1, int x2, int y2){
    return query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1);
}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int C, S;
    cin >> C >> S;
    while (true){
        cin >> C;
        if (C == 3) break;
        else if (C == 1){
            int X, Y, A;
            cin >> X >> Y >> A; X++; Y++;
            update(X, Y, A);
        }
        else if (C == 2){
            int L, B, R, T;
            cin >> L >> B >> R >> T; L++; R++; B++; T++;
            printf("%d\n", get_sum(L, B, R, T));
        }
    }
    return 0;
}
