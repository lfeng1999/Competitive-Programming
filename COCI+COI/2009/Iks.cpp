#include <bits/stdc++.h>

using namespace std;

int N, num[100], gcd = 1;
bool prime[1000000];

int moves(int p)
{
    int arr[100];
    memset(arr,0,sizeof(arr));
    int cnt = 0;
    for (int i=0; i!=N; ++i)
    {
        int a = num[i];
        while (a%p==0)
        {
            arr[i]++;
            a/=p;
        }
        cnt+=arr[i];
    }
    int avg = int(cnt/N);
    if (avg==0)
        return 0;
    int leftover = cnt - avg*N, addn = 0;
    for (int i=0; i!=N; ++i)
    if (arr[i] > avg)
        addn += arr[i] - avg;
    addn -= leftover;
    for (int i=0; i!=avg; ++i)
        gcd*=p;
    return addn;
}

int main()
{
    cin.sync_with_stdio(0);cin.tie(0);
    memset(prime,true,sizeof(prime));
    cin >> N;
    for (int i=0; i!=N; ++i)
        cin >> num[i];
    prime[0]=prime[1]=false;
    for (int i=2; i!=1000; ++i)
    if (prime[i])
        for (int j=i; i*j< 1000000; ++j)
            prime[i*j]=false;
    int tot = 0;
    for (int i=2; i!=1000000; ++i)
    if (prime[i])
        tot+=moves(i);
    cout << gcd << " " << tot;
}
