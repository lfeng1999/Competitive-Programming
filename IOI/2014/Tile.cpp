#include <bits/stdc++.h>

using namespace std;

void solve(int r, int c, int len, int br, int bc){
    if (len == 2){
        for (int r2 = r; r2 < r + 2; r2++){
            for (int c2 = c; c2 < c + 2; c2++){
                if (r2 != br || c2 != bc){
                    printf("%d %d ", r2, c2);
                }
            }
        }
        printf("\n");
        return;
    }
    len /= 2;
    vector<pair<int,int>> P;

    if (br < r + len && bc < c + len){
        solve(r, c, len, br, bc);
    }
    else{
        solve(r, c, len, r + len - 1, c + len - 1);
        P.push_back(make_pair(r + len - 1, c + len - 1));
    }

    if (br >= r + len && bc < c + len){
        solve(r + len, c, len, br, bc);
    }
    else{
        solve(r + len, c, len, r + len, c + len - 1);
        P.push_back(make_pair(r + len, c + len - 1));
    }

    if (br < r + len && bc >= c + len){
        solve(r, c + len, len, br, bc);
    }
    else{
        solve(r, c + len, len, r + len - 1, c + len);
        P.push_back(make_pair(r + len - 1, c + len));
    }

    if (br >= r + len && bc >= c + len){
        solve(r + len, c + len, len, br, bc);
    }
    else{
        solve(r + len, c + len, len, r + len, c + len);
        P.push_back(make_pair(r + len, c + len));
    }

    for (int i=0; i<P.size(); i++){
        printf("%d %d ", P[i].first, P[i].second);
    }
    printf("\n");
}

int main()
{
//    freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int n, r, c;
    cin >> n >> r >> c;
    solve(0, 0, 1 << n, r, c);
    return 0;
}
