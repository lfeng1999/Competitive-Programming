#include <bits/stdc++.h>

using namespace std;
//Pretty basic floodfill, except 3 dimensions
int n, gcount = 0;//gcount - amount of gold
bool gold[11][11][11], rock[11][11][11], passed[11][11][11];

bool valid(int a,int b,int c)
{
    if (rock[a][b][c] || passed[a][b][c] || a < 0 || b < 0 || c < 0 || a >= n || b >= n || c >=n)
        return false;
    return true;
}

void recur(int a,int b,int c)
{
    if (!valid(a,b,c))
        return;
    passed[a][b][c] = true;
    if (gold[a][b][c])
    {
        gcount++;
        gold[a][b][c] = false;
    }
    recur(a+1,b,c);
    recur(a,b+1,c);
    recur(a,b-1,c);
    recur(a,b,c+1);
    recur(a,b,c-1);
}


int main()
{
    cin.sync_with_stdio(0);cin.tie(0); //Just helps with efficiency
    cin >> n;
    for (int i=0; i!=n; ++i)
    for (int j=0; j!=n; ++j)
    for (int k=0; k!=n; ++k)
    {
        char p;
        cin >> p;
        if (p=='X')
            rock[i][j][k] = true;
        else if (p == '*')
            gold[i][j][k] = true;
    }
    for (int j=0; j!=n; ++j)
        for (int k=0; k!=n; ++k)
            recur(0,j,k);
//    cout << gcount; //Cout is slow as hell
    printf("%d",gcount);
}
