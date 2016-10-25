#include <bits/stdc++.h>

using namespace std;

int A[210], B[210];

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int N, p1=0, p2=0;
    cin >> N;
    for (int i=1; i<=N; ++i) cin >> A[i];
    for (int i=1; i<=N; ++i) cin >> B[i];
    
    for (int i=1; i<=N; ++i){
        if (A[i] > B[i]) p1++;
        else if (B[i] > A[i]) p2++;
    }
    cout << p1 << " " << p2 << endl;
    if (p1 > p2) cout << "Xyene";
    else if (p1 < p2) cout << "FatalEagle";
    else cout << "Tie";
    return 0;
}
