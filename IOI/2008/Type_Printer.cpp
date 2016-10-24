#include <bits/stdc++.h>

using namespace std;

#define MAXN 25010
#define MAXL 500100

class Trie
{
private:
    char ch[MAXL];
    int N, longest, extra;
    vector<int> graph[MAXL];
    int addchar(char c){
        ch[N] = c;
        return N++;
    }
public:
    Trie(){
        ch[0] = '\0';
        N = 1;
        longest = 0;
    }
    void insert(string &s){
        int node = 0;
        extra++;
        for (int i=0; i!=s.length(); i++){
            int j;
            for (j=0; j!=graph[node].size(); ++j){
                if (s[i] == ch[graph[node][j]]){
                    break;
                }
            }
            if (j != graph[node].size()){
                node = graph[node][j];
                continue;
            }
            graph[node].push_back(addchar(s[i]));
            node = N-1;
        }
    }
    int optimize(int node){
        if (ch[node] == 'z'+1){
            return 0;
        }
        int prev = 0, cur = 0, mlen = 0;
        for (int i=0; i!=graph[node].size(); ++i){
            cur = optimize(graph[node][i]);
            if (prev > cur){
                swap(graph[node][i-1], graph[node][i]);
            }
            else{
                prev = cur;
            }
            mlen = max(mlen, cur);
        }
        return mlen+1;
    }
    void print(int node, bool islongest){
        if (ch[node] == 'z'+1){
            printf("%c\n", 'P');
            return;
        }
        if (node){
            printf("%c\n", ch[node]);
        }
        for (int i=0; i<graph[node].size()-1; ++i){
            print(graph[node][i], false);
        }
        print(graph[node][graph[node].size()-1], islongest);
        if (!islongest){
            printf("%c\n",'-');
        }
    }
    void answer(){
        int longest = optimize(0) - 1;
        N--;
        printf("%d\n", 2*N-longest-extra);
        print(0, 1);
    }
};

Trie tree;

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int M;
    string s;
    cin >> M;
    for (int i=0; i!=M; ++i){
        cin >> s;
        s+='z' + 1;
        tree.insert(s);
    }
    tree.answer();
    return 0;
}
