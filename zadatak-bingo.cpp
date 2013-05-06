/*
 
C++ radionica
 
Zadatak: Bingo
 
Autor zadatka: Kristijan Burnik
 
Autor rjesenja: Kristijan Burnik
 
Datum rjesavanja: 2012-10-13
 
*/
#include <iostream>
#include <cstdlib>
 
 
using namespace std;
 
int main() {
 
    int n,k;
   
    cin >> n >> k;  
   
    string igrac[n];
    for (int i = 0 ; i < n; i++)
        cin >> igrac[i];
     
    string listic[k];
    for (int i = 0 ; i < k; i++)
        cin >> listic[i];
 
 
    for (int i = 0 ; i < n; i++) {
        cout << igrac[i] << ": ";
        for (int j = i; j < k; j += n) {
            cout << listic[j] << " ";
        }
        cout << endl;
    }
 
 
    system("pause");
 
    return 0;
}