#include <bits/stdc++.h>

using namespace std;

int N, G;
int occur[1025][1025];


int main()
{
//    freopen("CCO.in","r",stdin);
    scanf("%d%d",&N,&G);
    memset(occur, 0, sizeof(occur));

    for (int qq=0; qq<G; ++qq){
        int grid[10][10];
        memset(grid, 0, sizeof(grid));

        for (int i=0; i<N; ++i){
            char arr[10];
            scanf("%s", arr);
            for (int j=0; j<N; ++j){
                grid[i][j] = (arr[j] == 'R');
            }
        }

        for (int i = N-1; i>=1; --i){
            for (int j=N-1; j>=1; --j){
                if (grid[i][j] == 1){
                    grid[i][j] ^= 1;
                    grid[i][j-1] ^= 1;
                    grid[i-1][j] ^= 1;
                    grid[i-1][j-1] ^= 1;
                }
            }
        }

        int x = 0, p2 = 1;
        for (int i=0; i<N; ++i){
            x += p2*grid[i][0];
            p2 *= 2;
        }
        p2 = 1;
        int y = 0;
        for (int i=0; i<N; ++i){
            y += p2*grid[0][i];
            p2 *= 2;
        }

        occur[x][y]++;
    }
    int ans = 0;
    for (int i=0; i<1024; ++i){
        for (int j = 0; j<1024; ++j){
            ans += (occur[i][j])*(occur[i][j] - 1)/2;
        }
    }
    cout << ans;

    return 0;
}