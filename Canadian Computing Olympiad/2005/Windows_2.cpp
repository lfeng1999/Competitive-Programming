#include <bits/stdc++.h>

using namespace std;

struct Node2{ //Y segment tree
    int L, R;
    Node2 *left = NULL, *right = NULL;
    Node2(int L, int R) :
        L(L), R(R) {}
    vector<int> rects;
};

struct Node1{ //Original
    int L, R;
    Node1 *left = NULL, *right = NULL;
    Node2 *root = NULL; //Y root
    Node1(int L, int R) :
        L(L), R(R) {}
};

struct Window{
    int x1, y1, x2, y2, id, p;
} windows[50010];

int CC, RR;

Node2 *update2(Node2 *root, int L, int R, Window &wind){
    int y1 = wind.y1, y2 = wind.y2, id = wind.id;

    if (R < y1 || y2 < L) return root;

    if (!root) root = new Node2(L, R);

    if (y1 <= L && R <= y2){
        root->rects.push_back(id);
    }
    else{
        root->left = update2(root->left, L, (L+R)/2, wind);
        root->right = update2(root->right, (L+R)/2 + 1, R, wind);
    }
    return root;
}

Node1 *update1(Node1 *root, int L, int R, Window &wind){
    int x1 = wind.x1, x2 = wind.x2, id = wind.id;

    if (R < x1 || x2 < L) return root;

    if (!root) root = new Node1(L, R);

    if (x1 <= L && R <= x2){
        root->root = update2(root->root, 1, RR, wind);
    }
    else{
        root->left = update1(root->left, L, (L+R)/2, wind);
        root->right = update1(root->right, (L+R)/2 + 1, R, wind);
    }
    return root;
}
int best = 0, bestid = 0;

void query2(Node2 *root, int x, int y){

    if (!root) return;

    int L = root->L, R = root->R;

    if (R < y || y < L) return;

    if (L <= y && y <= R){
        for (int v : root->rects){
            if (windows[v].p > best){
                best = windows[v].p;
                bestid = windows[v].id;
            }
        }
    }
    if (L != R){
        query2(root->left, x, y);
        query2(root->right, x, y);
    }


}

void query1(Node1 *root, int x, int y){
    if (!root) return;

    int L = root->L, R = root->R;

    if (R < x || x < L) return;

    if (L <= x && x <= R){
        query2(root->root, x, y);
    }

    if (L != R){
        query1(root->left, x, y);
        query1(root->right, x, y);
    }
}

int main()
{
//    freopen("CCO.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> CC >> RR;
    Node1 *root = new Node1(1, CC);

    int N;
    cin >> N;
    for (int i = 1; i<=N; ++i){
        cin >> windows[i].x1 >> windows[i].y2 >> windows[i].x2 >> windows[i].y1;
        windows[i].id = i;
        windows[i].p = i;
        update1(root, 1, CC, windows[i]);
    }
    int QQ;
    cin >> QQ;
    for (int i=1; i<=QQ; ++i){
        best = 0, bestid = 0;
        int x, y; cin >> x >> y;

        query1(root, x, y);
        printf("%d\n", bestid);

        windows[bestid].p = i + N;
    }

    return 0;
}
