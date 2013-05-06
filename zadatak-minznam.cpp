/*
    Zadatak: MinZnam
     
            Za niz od N cijelih brojeva (int), iz svakog dohvatiti najmanju
            znamenku i od tih znamenki redom sastaviti novi broj
            (proizvoljne duljine) kojeg ispisujemo.
             
    Rješenje: Kristijan Burnik, Udruga informatièara Božo Težak
              GMail: kristijanburnik
             
    Složenost: O(N)
               obrada znamenki koje mozemo zapisati s int podrazumijevano O(1)
   
   
    Datum: 24.01.2012.
   
    Test primjer: [Ulaz]: 3 111 278 997 [Izlaz]: 127
 
*/
#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int najmanja_znamenka(int broj) {
   
    // za pretpostavljeni minimum uvijek uzimamo maksimalnu mogucu vrijednost
    // koja ovdje iznosi 9
    // a onda kad je moguce i korisno, rabimo prvi element iz zadanog niza
    int minznam = 9;
    // Cijepamo znamenke s desna na lijeve i tražimo minimum
    while (broj > 0){
        // izvuci najmanje znaèajnu znamenku
        int znamenka = broj % 10;
        // odredi novi mimimum
        minznam = min (znamenka,minznam);
        // ukoni obradjenu znamenku
        broj /= 10;
    }  
    return minznam;
}
 
int main(void) {
   
    // koliko cemo imati ulaza?
    int n;
    cin >> n;
 
    int broj; // trenutni broj koji obradjujemo
    string izlaz; // izlazni string
   
    for (int i = 0; i < n ; i++) {
        // unesi broj
        cin >> broj;
        // dohvati najmanju znamenku
        int min = najmanja_znamenka(broj);
        // pretvori znamenku u znak te napravi konkatenaciju na izlazni string
        izlaz += (char)(min + '0');
    }
   
    // ispisi izlazni string
    cout << izlaz << endl;
 
//  system("pause");
 
 
    return 0;
}