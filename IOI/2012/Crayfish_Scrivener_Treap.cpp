#include <bits/stdc++.h>

using namespace std;

struct Node{
    int val, p;
    int size;
    Node *left, *right;
};

int RandomPriority(){
    return (rand() << 16) | rand();
}

int Size(Node *root){
    if (!root) return 0;
    return root->size;
}

Node* makeNode(int val, int p, Node *left, Node *right){
    Node* ans = new Node();
    ans->val = val;
    ans->p = p;
    ans->left = left;
    ans->right = right;
    ans->size = 1 + Size(left) + Size(right);

    return ans;
}

Node* Merge(Node *a, Node *b){//WLOG a's vals are all less than b's
    if (!a) return b;
    if (!b) return a;

    if (a->p < b->p){
        return makeNode(a->val, a->p, a->left, Merge(a->right, b));
    }
    return makeNode(b->val, b->p, Merge(a, b->left), b->right);
}

pair<Node*, Node*> Split(Node *root, int v){
    if (!root) return make_pair(nullptr, nullptr);

    if (v > root->val){
        pair<Node*, Node*> temp = Split(root->right, v);
        temp.first = makeNode(root->val, root->p, root->left, temp.first);
        return temp;
    }
    pair<Node*, Node*> temp = Split(root->left, v);
    temp.second = makeNode(root->val, root->p, temp.second, root->right);
    return temp;
}

Node* insert(Node *root, int val){
    pair<Node*, Node*> splitted = Split(root, val);
    Node* temp = makeNode(val, RandomPriority(), nullptr, nullptr);

    return Merge(splitted.first, Merge(temp, splitted.second));
}

Node* Lookup(Node *root, int idx){
    if (Size(root->left) > idx)
        return Lookup(root->left, idx);
    idx -= Size(root->left);
    if (idx == 0) return root;
    idx--;

    return Lookup(root->right, idx);
}

int main()
{
//    freopen("IOI.in","r",stdin);
    int nCommands;
    cin >> nCommands;
    vector<Node*> states;
    states.push_back(nullptr);
    int cur_state = 1;
    while (nCommands--){
        char buf[10];
        scanf("%s",buf);
        if (*buf == 'T'){
            scanf("%s", buf);
            states.push_back(Merge(states[cur_state-1], makeNode(*buf, RandomPriority(), nullptr, nullptr)));
            cur_state++;
        }
        else if (*buf == 'U'){
            int x;
            scanf("%d", &x);
            states.push_back(states[cur_state - x - 1]);
            cur_state++;
        }
        else if (*buf == 'P'){
            int x;
            scanf("%d", &x);
            printf("%c\n", Lookup(states[cur_state - 1], x)->val);
        }
    }
    return 0;
}
