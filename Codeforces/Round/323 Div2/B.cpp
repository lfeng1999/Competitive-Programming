#include <bits/stdc++.h>

using namespace std;

int T[1010];
bool done[1010];

int main()
{
    //freopen("IOI.txt","r",stdin);
    int N;
    cin >> N;
    for (int i=0; i!=N; ++i){
        cin >> T[i];
    }
    bool valid = false;
    int cnt = 0, cd = 0;
    while (!valid){
        valid = true;
        if (!(cd%2)){
            for (int i=0; i!=N; ++i){
                if (cnt>=T[i] && !done[i]){
                    done[i]  = true;
                    valid = false;
                    cnt++;
                }
            }
        }
        else{
            for (int i=N-1; i>=0; --i){
                if (cnt>=T[i] && !done[i]){
                    done[i]  = true;
                    valid = false;
                    cnt++;
                }
            }
        }
        cd++;
    }
    cout << cd - 2;
    return 0;
}