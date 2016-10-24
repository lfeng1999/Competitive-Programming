#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000010
#define LOGN 21

int state[MAXN];

class tree
{
private:
    int ances[MAXN][LOGN], N;
    char key[MAXN];
    int get_len(int i){
        int n = 1;
        for (int log = 20; log >= 0; --log){
            if (ances[i][log] < 0){
                continue;
            }
            i = ances[i][log];
            n += (1 << log);
        }
        return n;
    }
public:
    tree(){
        memset(ances,-1,sizeof(ances));
    }
    int insert(int i, char c){
        ances[N][0] = i;
        int log = 1;
        for (; ances[N][log-1] >= 0; ++log){
            ances[N][log] = ances[ances[N][log-1]][log-1];
        }
        key[N] = c;
        return N++;
    }
    char query(int i, int p){
        p = get_len(i) - p - 1; // starts from 0
        for (int log = 20; log >= 0; --log){
            if ((1 << log) > p){
                continue;
            }
            i = ances[i][log];
            p-=(1 << log);
        }
        return key[i];
    }
};

tree tr;
int p, qq, N;
char cmd, c;

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> qq;
    while (qq--){
        cin >> cmd;
        if (cmd == 'T'){ // Type
            cin >> c;
            state[N] = tr.insert(N?state[N-1]:-1,c);
            N++;
        }
        else if (cmd == 'U'){ // Undo
            cin >> p;
            state[N] = state[N-p-1];
            N++;
        }
        else if (cmd == 'P'){ // Get
            cin >> p;
            printf("% c \n", tr.query(state[N-1],p));
        }
    }

    return 0;
}
