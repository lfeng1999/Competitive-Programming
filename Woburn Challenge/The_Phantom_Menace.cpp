#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;

int N, M, R, C, nums[10010];

int main()
{
 //   freopen("Woburn.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i){
        cin >> nums[i];
    }
    for (int i=1; i<=N; ++i){
        if (nums[i] == 0){
            if (nums[i+1]==1){
                if (nums[i-1] == 2){
                    nums[i] = 3;
                }
                else{
                    nums[i] = 2;
                }
            }
            else if (nums[i-1] == 1){
                if (nums[i+1] == 2){
                    nums[i] = 3;
                }
                else{
                    nums[i] = 2;
                }
            }
            else{
                nums[i] = 1;
            }
        }
    }
    for (int i=1; i<=N; ++i){
        cout << nums[i];
    }

    return 0;
}
