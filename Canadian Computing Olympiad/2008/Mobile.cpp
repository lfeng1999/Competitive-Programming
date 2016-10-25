#include <bits/stdc++.h>

using namespace std;

struct node
{
    int lef = 0, rig = 0;
};
int N, N2;
node tree[200010], tree2[200010];

bool cmp(node &n1, node &n2)
{
    if (n1.lef < 0 && n2.lef < 0)
    {
        if (n1.rig < 0  && n2.rig < 0)
        {
            if ((n1.lef == n2.lef && n1.rig == n2.rig) || (n1.lef == n2.rig && n1.rig == n2.lef))
                return true;
        }
        else if (n1.rig > 0 && n2.rig > 0 && n1.lef == n2.lef)
            return cmp(tree[n1.rig], tree2[n2.rig]);
    }
    else if (n1.lef < 0 && n1.rig > 0 && n2.lef > 0 && n2.rig < 0)
    {
        if (n1.lef == n2.rig && cmp(tree[n1.rig],tree2[n2.lef]))
            return true;
    }
    else if (n1.lef > 0 && n1.rig < 0 && n2.lef < 0 && n2.rig > 0)
    {
        if (n1.rig == n2.lef && cmp(tree[n1.lef],tree2[n2.rig]))
            return true;
    }
    else if (n1.lef > 0 && n2.lef > 0)
    {
        if (n1.rig > 0 && n2.rig > 0)
        {
            if ((cmp(tree[n1.lef], tree2[n2.lef]) && cmp(tree[n1.rig], tree2[n2.rig])) || (cmp(tree[n1.lef], tree2[n2.rig]) && cmp(tree[n1.rig], tree2[n2.lef])))
                return true;
        }
        else if (n1.rig < 0 && n2.rig < 0 && n1.rig == n2.rig)
        {
            return cmp(tree[n1.lef], tree2[n2.lef]);
        }
    }

    return false;
}


int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i)
    {
        int a,b;
        cin >> a >> b;
        tree[i].lef = a, tree[i].rig = b;
    }
    cin >> N2;
    for (int i=1; i<=N2; ++i)
    {
        int a,b;
        cin >> a >> b;
        tree2[i].lef = a, tree2[i].rig = b;
    }
    if (cmp(tree[1], tree2[1]))
        cout << "Fred and Mary might have the same mobile.";
    else
        cout << "Fred and Mary have different mobiles.";
}
