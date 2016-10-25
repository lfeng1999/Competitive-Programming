#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("CCC.txt","r",stdin);
    int QQ; cin >> QQ;
    while (QQ--){
        int N;
        cin >> N;
        int sum = 0;
        for (int i=1; i<N; ++i){
            if (N%i == 0) sum+=i;
        }
        if (sum == N){
            printf("%d is a perfect number.\n", N);
        }
        else if (sum < N){
            printf("%d is a deficient number.\n", N);
        }
        else{
            printf("%d is an abundant number.\n", N);
        }
    }

    return 0;
}
