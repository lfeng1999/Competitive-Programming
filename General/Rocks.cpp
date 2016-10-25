#include <bits/stdc++.h>

using namespace std;

struct Node{
    int L, R, mass_sum;
}seg[40010];

int orig[10010], lookup[10010];
map<string, int> lookup_pos;

void build_tree(int v, int L, int R){
    seg[v].L = L, seg[v].R = R;
    if (L == R){
        lookup[L] = v;
        return;
    }
    build_tree(v*2, L, (L+R)/2);
    build_tree(v*2+1, (L+R)/2+1, R);
}

int query_mass(int v, int L, int R){
    if (R < seg[v].L || seg[v].R < L) return 0;
    if (L <= seg[v].L && seg[v].R <= R){
        return seg[v].mass_sum;
    }
    return query_mass(v*2, L, R) + query_mass(v*2+1, L, R);
}

void add_rock(int v, int pos, int mass){
    if (seg[v].L == seg[v].R){
        seg[v].mass_sum = mass;
        return;
    }
    if (pos <= (seg[v].L+seg[v].R)/2){
        add_rock(v*2, pos, mass);
    }
    else{
        add_rock(v*2+1, pos, mass);
    }
    seg[v].mass_sum = seg[v*2].mass_sum + seg[v*2+1].mass_sum;
}

int calc_mass(string S){
    int val = 0;
    for (int i=0; i<S.length(); ++i){
        val += S[i] - 'a' + 1;
    }
    return val;
}

int main()
{
//    freopen("Mac.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    build_tree(1, 1, 10000);
    int C, cur = 1;
    cin >> C;
    while (C--){
        char ch; string s1, s2;
        cin >> ch;
        if (ch == 'A'){
            cin >> s1;
            if (lookup_pos.count(s1) && lookup_pos[s1]!=-1){
                printf("Can't add %s\n", s1.c_str());
            }
            else{
                lookup_pos[s1] = cur;
                add_rock(1, cur, calc_mass(s1));
                cur++;
            }
        }
        else if (ch == 'S'){
            cin >> s1 >> s2;
            add_rock(1, lookup_pos[s1], calc_mass(s2));
            add_rock(1, lookup_pos[s2], calc_mass(s1));
            swap(lookup_pos[s1], lookup_pos[s2]);
        }
        else if (ch == 'M'){
            cin >> s1 >> s2;
            if (lookup_pos[s2] < lookup_pos[s1]) swap(s1,s2);
            printf("%d\n", query_mass(1, lookup_pos[s1], lookup_pos[s2]));
        }
        else if (ch == 'R'){
            cin >> s1 >> s2;
            add_rock(1, lookup_pos[s1], calc_mass(s2));
            lookup_pos[s2] = lookup_pos[s1];
            lookup_pos[s1] = -1;
        }
        else if (ch == 'N'){
            printf("%d\n", cur-1);
        }
    }
    return 0;
}