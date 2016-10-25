#include <bits/stdc++.h>

using namespace std;

vector<int> in_col[100010];
int N, grid[3][100010], occur[3][100010], que[100010], q_head = 0, q_tail = 0;
bool inq[100010];

int main()
{
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N;

    for (int i=0; i<3; ++i){
        for (int j=0; j<N; ++j){
            cin >> grid[i][j];
            occur[i][grid[i][j]]++;
            in_col[grid[i][j]].push_back(j);
        }
    }
    for (int i=0; i<N; ++i){
        if (occur[1][grid[0][i]] == 0 || occur[2][grid[0][i]] == 0){
            que[q_tail++] = i;
            inq[i] = true;
        }
    }
    int ans = 0;
    while (q_head != q_tail){

        int col = que[q_head++];

        for (int i=0; i<3; ++i){
            occur[i][grid[i][col]]--;
            if (occur[i][grid[i][col]] == 0){

                for (int v : in_col[grid[i][col]]){
                    if (inq[v]) continue;
                    inq[v] = true;
                    que[q_tail++] = v;
                }
            }
        }
    }
    cout << q_tail;
    return 0;
}
