#include <bits/stdc++.h>

using namespace std;

vector<int> ttemp;

int main()
{
    ttemp.push_back(0);
    int a,b,maxt = 0;
    cin >> a >> b;
    for (int i=1; i<=a; ++i)
    {
        int c;
        cin >> c;
        ttemp.push_back(ttemp[i-1]+c);
        maxt = max(maxt,ttemp[i] - ttemp[int(max(i-b,0))]);
    }
    cout << maxt;
}