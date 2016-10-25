#include <bits/stdc++.h>

using namespace std;

int N, Q;
char words[30010][32];

struct Word{
    char str[32];
    int id;
    bool operator < (const Word &a) const{
        return lexicographical_compare(str, str + 32, a.str, a.str + 32);
    }
};

vector<Word> sorted;

int begin_col[32], end_col[32], occur[30010][32], before[30010][32];

int find_border(char ch, int cur, int L, int R){
    while (L < R){
        int mid = (L+R)/2;
        if (sorted[mid].str[cur] >= ch)
            R = mid;
        else
            L = mid + 1;
    }
    return L;
}

int setup(char *s, int cur, int L, int R){
    begin_col[cur] = end_col[cur] = -1;

    if (s[cur] == 0){
        if (sorted[L].str[cur] == 0) return L;
        return -1;
    }

    begin_col[cur] = find_border(s[cur], cur, L, R);
    end_col[cur] = find_border(s[cur] + 1, cur, L, R); //not including the end

    if (begin_col[cur] == end_col[cur]) return -1;

    return setup(s, cur + 1, begin_col[cur], end_col[cur]);
}

int main()
{
//    freopen("COCI.in","r",stdin);

    scanf("%d", &N);
    for (int i=0; i<N; ++i){
        scanf("%s",&words[i]);
        sorted.push_back(Word());
        strcpy(sorted[i].str, words[i]);
        sorted[i].id = i;
    }
    sort(sorted.begin(), sorted.end());

    for (int i=0; i<N; ++i){
        setup(words[i], 0, 0, N);

        for (int j=0; begin_col[j] < end_col[j]; j++){
            before[i][j] = ++occur[begin_col[j]][j];
        }
    }
    int M;
    scanf("%d", &M);
    for (int qq = 0; qq < M; ++qq){
        char s[32];
        scanf("%s", &s);

        int row = setup(s, 0, 0, N);
        int ans = 0;
        if (row == -1){
            ans = N;
            for (int j = 0; begin_col[j] < end_col[j]; ++j){
                ans += end_col[j] - begin_col[j];
            }
        }
        else{
            ans = sorted[row].id + 1;
            for (int j = 0; begin_col[j] < end_col[j]; ++j){
                ans += before[sorted[row].id][j];
            }
        }
        printf("%d\n", ans);
    }


    return 0;
}
