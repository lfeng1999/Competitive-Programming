#include <bits/stdc++.h>

using namespace std;

int N, balls[410], psum[410];
bool works[410][410];

int ricesum(int i, int j){
    return psum[j] - psum[i-1];
}

int main()
{
//    freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i){
        cin >> balls[i];
        psum[i] = balls[i] + psum[i-1];
        works[i][i] = true;
    }
    for (int len=1; len<=N-1; ++len){ //Try every length of combining
        for (int i=1; i<=N-len; ++i){ //First starting position
            //Try next to each other
            for (int j=i; j<i+len; ++j){
                if (works[i][j] && works[j+1][i+len] && ricesum(i, j) == ricesum(j+1, i+len)){
                    works[i][i+len] = true;
                }
            }
            //Try something in the middle

            int a = i+1, b = i + len - 1;
            int leftsum, rightsum;
            while (a <= b){ //i-th to (a-1)-th must be combinable and a-th to b-th must be combinable and (b+1)-th to (i+len)-th must be combinable
                leftsum = ricesum(i, a-1), rightsum = ricesum(b+1, i+len);
                if (leftsum == rightsum){
                    if (works[i][a-1] && works[a][b] && works[b+1][i+len]){
                        works[i][i+len] = true;
                        break;
                    }
                    else{
                        a++; b--;
                    }
                }
                else if (leftsum < rightsum) a++;
                else if (rightsum < leftsum) b--;
            }
        }
    }
    int ans = 0;
    for (int i=1; i<=N; ++i){
        for (int j=i; j<=N; ++j){
            if (works[i][j]){
                ans = max(ans, ricesum(i, j));
            }
        }
    }
    cout << ans;


    return 0;
}