/*
 
TEMA : Binarno stablo i suma svih cvorova u preorder obilasku
 
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
 
int suma(node *p) {
    if (p == NULL) return 0;
    return p->val + suma(p->left) + suma(p->right);  
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
   
    cout << "suma: " << suma(&stablo[1]);
    cout << endl;
 
    system("pause");
    return 0;
}