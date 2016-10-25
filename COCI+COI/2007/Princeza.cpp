#include <bits/stdc++.h>

using namespace std;

struct plant{
    int x, y, id, dif, sum;
    int quad[4] = {-1, -1, -1, -1};
} plants[100010];

bool pos_cmp(plant p1, plant p2){
    if (p1.dif != p2.dif)
        return p1.dif < p2.dif;
    return p1.y < p2.y;
}
bool neg_cmp(plant p1, plant p2){
    if (p1.sum != p2.sum)
        return p1.sum < p2.sum;
    return p1.y < p2.y;
}

bool id_cmp(plant p1, plant p2){
    return p1.id < p2.id;
}

int N, K;
string moves;

int main()
{
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    cin >> moves;

    for (int i = 0; i < N; ++i){
        cin >> plants[i].x >> plants[i].y;
        plants[i].id = i;
        plants[i].dif = plants[i].y - plants[i].x;
        plants[i].sum = plants[i].y + plants[i].x;
    }
    sort(plants, plants + N, pos_cmp);

    for (int i = 0; i < N - 1; ++i){
        if (plants[i].dif == plants[i+1].dif){
            plants[i].quad[0] = plants[i+1].id;
            plants[i+1].quad[2] = plants[i].id;
        }
    }
    sort(plants, plants + N, neg_cmp);

    for (int i = 0; i < N - 1; ++i){
        if (plants[i].sum == plants[i+1].sum){
            plants[i].quad[1] = plants[i+1].id;
            plants[i+1].quad[3] = plants[i].id;
        }
    }
    sort(plants, plants + N, id_cmp);
    int cur_id = 0;

    for (int i=0; i<K; ++i){
        int quad[4];
        for (int j=0; j<4; ++j)
            quad[j] = plants[cur_id].quad[j];

        if (moves[i] == 'A'){
            if (quad[0] == -1)
                continue;
            cur_id = quad[0];
        }
        else if (moves[i] == 'B'){
            if (quad[3] == -1)
                continue;
            cur_id = quad[3];
        }
        else if (moves[i] == 'C'){
            if (quad[1] == -1)
                continue;
            cur_id = quad[1];
        }
        else if (moves[i] == 'D'){
            if (quad[2] == -1)
                continue;
            cur_id = quad[2];
        }

        if (quad[0] != -1)
            plants[quad[0]].quad[2] = quad[2];

        if (quad[1] != -1)
            plants[quad[1]].quad[3] = quad[3];

        if (quad[2] != -1)
            plants[quad[2]].quad[0] = quad[0];

        if (quad[3] != -1)
            plants[quad[3]].quad[1] = quad[1];
    }

    cout << plants[cur_id].x << " " << plants[cur_id].y;

    return 0;
}
