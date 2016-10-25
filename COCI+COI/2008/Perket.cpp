#include <bits/stdc++.h>

using namespace std;

int best = 0x7fffffff, N, sour[10], bitter[10];
void bash(int cnt, int s, int b)
{
    if (cnt == N)
    {
        if (s==0 && b==0)
            return;
        best = min(best,abs(s-b));
        return;
    }
    bash(cnt+1,s,b);
    if (s==0)
        s=1;
    bash(cnt+1,s*sour[cnt],b+bitter[cnt]);

}
int main()
{
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> N;
    for (int i=0; i!=N; ++i)
        cin >> sour[i] >> bitter[i];
    bash(0,0,0);
    cout << best;
    return 0;
}
