/*
 
TEMA : Binarno stablo i tri tipicna obilaska
 
Autor zadatka: Kristijan Burnik
 
Autor rjesenja: Kristijan Burnik
 
Datum rjesavanja: 2012-10-06
     
Primjer:
5            
10 20 30 40 50            
2
1 2 3        
2 4 5      
 
*/
#include <iostream>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
typedef struct node {
        int val;
        node *left;
        node *right;        
} node;
 
/////////////////////////////////
 
void handle(node *p) {
     cout << p->val << " ";
}
 
void preorder(node *p) {
     if (p == NULL) return;
     handle(p);
     preorder(p->left);
     preorder(p->right);
}
 
void inorder(node *p) {
     if (p == NULL) return;
     inorder(p->left);
     handle(p);
     inorder(p->right);
}
 
void postorder(node *p) {
     if (p == NULL) return;
     postorder(p->left);
     postorder(p->right);
     handle(p);
}
 
 
 
int main() {
 
    int n;
    cin >> n;
   
    vector < node > stablo;    
    stablo.resize( n + 1 ) ;
    for (int i = 1;  i <= n; i++) {
        cin >> stablo[i].val;
    }
   
    int m;
    cin >> m;
    int p,l,r;
    for (int i = 0 ; i < m ; i++) {
        cin >> p >> l >> r;
        stablo[p].left = &stablo[l];
        stablo[p].right  = &stablo[r];
    }
   
   
    cout << "preorder: ";
    preorder(&stablo[1]);
    cout << endl;
   
    cout << "inorder: ";
    inorder(&stablo[1]);
    cout << endl;
   
    cout << "postorder: ";
    postorder(&stablo[1]);
    cout << endl;
 
 
    system("pause");
    return 0;
}