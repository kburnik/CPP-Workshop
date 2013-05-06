#include <iostream>
#include <cstdio>
#include <map>
 
using namespace std;
 
map < string , pair < string , string > > stablo;
 
 
int obilazak(string pocetak, string trazi, string put) {
        if (pocetak.size() == 0) {
            return 0;
        }
       
        put += pocetak;
       
        if (pocetak == trazi) {
            cout << put << endl;
            return 1;
        } else {
            put += " -> ";
            return
                obilazak(stablo[pocetak].first, trazi, put)
                + obilazak(stablo[pocetak].second, trazi, put)
            ;
        }
}
 
 
int main() {
   
 
    int n;
    cin >> n;
   
    string x,l,d,root;
    for (int i = 0; i < n; i++) {
        cin >> x >> l >> d;
        stablo[x] = make_pair(l,d);
        if (i == 0) root = x;
    }
   
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (!obilazak(root,x,"")) {
            cout << "Nema puta!" << endl;
        }
    }
   
    return 0;    
}