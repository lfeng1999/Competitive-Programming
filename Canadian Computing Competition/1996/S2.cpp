#include <bits/stdc++.h>

using namespace std;

int arr[51];

int main()
{
    //freopen("CCC.txt","r",stdin);
    int QQ, len;
    cin >> QQ;
    while (QQ--){
        memset(arr, 0, 51);
        string S;
        cin >> S; len = S.length();
        for (int i=0; i<len; ++i){
            arr[i] =  S[len-1-i] - '0';
        }
        for (int i=0; i<len-2; ++i){
            for (int j=len-1; j>=i; --j){
                if (j == len-1 && arr[j] == 0){
                    len--;
                    continue;
                }
                printf("%d", arr[j]);
            }
            printf("\n");
            arr[i+1] -= arr[i];
            arr[i] = 0;

            int j = i+1;
            while (arr[j] < 0){
                arr[j+1]--;
                arr[j]+=10;
                j++;
            }
        }
        if (arr[len-1] != 0)
            printf("%d", arr[len-1]);
        printf("%d\n", arr[len-2]);

        int x = arr[len-1]*10 + arr[len-2];
        if (x%11 == 0){
            printf("The number %s is divisible by 11.\n\n", S.c_str());
        }
        else{
            printf("The number %s is not divisible by 11.\n\n", S.c_str());
        }
    }

    return 0;
}
