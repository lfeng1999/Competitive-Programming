#include<iostream>
#include<cstdio>
#include<map>
using namespace std;

int n, q, a, ans, last; char ch;
struct node{
    int size, value;
    node* left; node* right;
    node(int v){
        left=0; right=0; size=1; value=v;
    }
} *root;
int size(node* T){
    if (T==0) return 0; return T->size;
}
void resize(node*& T){
    T->size=size(T->left)+size(T->right)+1;
}
int rotl(node*& T){
    node* k=T->right;
    T->right=k->left;
    k->left=T; T=k;
    resize(T->left); resize(T);
}
int rotr(node*& T){
    node* k=T->left;
    T->left=k->right;
    k->right=T; T=k;
    resize(T->right); resize(T);
}
void balance(node*& t, bool F){
    if (t==0) return; 
    bool updated = false;
    if (t->left){
        if (size(t->left->right)>size(t->right)){
            rotl(t->left); rotr(t);
            updated = true;
        }
        else if (size(t->left->left)>size(t->right)){
            rotr(t);
            updated = true;
        }
    }
    if (t->right){
        if (size(t->right->left)>size(t->left)){
            rotr(t->right); rotl(t);
            updated = true;
        }
        else if (size(t->right->right)>size(t->left)){
            rotl(t);
            updated = true;
        }
    }
    if (updated){

        balance(t->left, 0); balance(t->right, 1);
        balance(t, 0);   
    }
}
void add(int val, node*& t){
    if (t==0){
        t=new node(val); return;
    }
    if (val<=t->value){
        add(val, t->left); balance(t, 1);
    } else{
        add(val, t->right); balance(t, 0);
    }
    resize(t);
}
void erase(int val, node*& t){
    if (t==0) return;
    if (val<t->value){
        erase(val, t->left);
    }
    else if(val>t->value){
        erase(val, t->right);
    } else {
        if (t->left==0 || t->right==0){
            node *tmp;
            if (t->left==0) tmp=t->right;
            else tmp=t->left; 
            delete t;
            t = tmp;
            return;
        } else {
            node* k=t->right;
            while(k->left!=0) k=k->left;
            t->value=k->value; erase(k->value, t->right);
        }
    }
    resize(t);
}
int rank(int R, node* t){
    if (R==size(t->left)) return t->value;
    if (R<size(t->left)) return rank(R, t->left);
    return rank(R-size(t->left)-1, t->right);
}
void top(int val, int S, node*& t){
    if (t==0){
        return;
    }
    if (val<=t->value){
        if (val==t->value){
            ans=S+size(t->left);
        }
        top(val, S, t->left);
    } else{
        top(val, S+size(t)-size(t->right), t->right);
    }
}
void dfs(node*t){
    if (t==0) return;
    dfs(t->left);
    printf("%i ", t->value);
    dfs(t->right);
}
int main(){
    scanf("%i%i", &n, &q);
    for (int l=0; l<n; ++l){
        scanf("%i", &a);
        add(a, root);
    }
    for (int l=0; l<q; ++l){
        scanf(" %c%i", &ch, &a);
        a= a ^ last;
        //cout << a << ' ' << last <<' ';
        if (ch=='S'){
            printf("%i\n", last=rank(a-1, root));
        } else if (ch=='I'){
            add(a, root);
        } else if (ch=='R'){
            erase(a, root);
        } else {
            ans=-2; top(a, 0, root);
            printf("%i\n", last=ans+1);
        }
    }
    dfs(root);
    return 0;
}