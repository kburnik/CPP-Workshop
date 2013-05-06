/*
C++ radionica za napredne osnovce
 
TEMA : Memoizacija
 
Autor zadatka: Kristijan Burnik
 
Autor rjesenja: Kristijan Burnik
 
Datum rjesavanja: 19.10.2012.
 
*/
#include <iostream>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
int calls = 0;
int fib(int n) {
    calls++;
    return (n <= 2) ? 1 : (fib(n-2)+fib(n-1));
}
 
 
vector <long long> rj;
 
long long fib2(int n) {
     calls ++ ;
     if (rj.size() < (n+1))
        rj.resize(n+1);
       
     if (rj[n] > 0) return rj[n];
     
     return rj[n] = (n <= 2) ? 1 : fib2(n - 2) + fib2(n - 1);
}
 
int main() {
 
    int koji = 0;
    cout << "Fib (rekurzivno) ili Fib2 (rekurzivno + memoizacija) ? " << endl << "Upisati 1 ili 2: ";
    cin >> koji;
   
    cout << "N = ";
 
   
    if (koji == 1) {
       int n;
       cin >> n;
   
        for (int i = 1; i <= n; i++) {
           calls = 0 ;
           cout << i << " " << fib(i) << " : " << calls << endl;
        }
             
    } else {
        int n;
        cin >> n;
   
        for (int i = 1; i <= n; i++) {
           rj.resize(0);
           calls = 0 ;
           cout << i << " " << fib2(i) << " : " << calls << endl;
        }
           
    }
 
    system("pause");
    return 0;
}