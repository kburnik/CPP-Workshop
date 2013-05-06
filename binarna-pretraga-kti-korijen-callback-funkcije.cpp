/*
 
TEMA : Računanje K-tog korijena
 
Autor zadatka: Kristijan Burnik, udruga informatičara Božo Težak
 
Autor rjesenja: Kristijan Burnik, udruga informatičara Božo Težak
 
Datum rjesavanja: 2012-10-27
 
*/
#include <iostream>
#include <cstdlib>
 
 
using namespace std;
 
// preciznost tipa podatka
typedef long double real;
 
 
// prototip callback funkcije
typedef real (*Callback)(real a, real b);
 
 
// preciznost računanja
const real preciznost = 0.0000000001;
 
// binarana pretraga
real binarno(real s, real e, real p, real n, Callback cmp) {
     real t = 0;
     
     // dok je razlika gornje i donje granice veća od zadane preciznosti
     while  ( (e-s) > p ) {
            // računanje sredine - odabiremo kandidata za usporedbu
            t = (s+e)/2;            
           
            // poziv callback funkcije, samo ovdje se koristi parametar n !
            real usp = (*cmp)(t,n);
           
 
            if ( usp > 0 && (usp <= p) || usp < 0 && (-usp <= p)) {
               // ako je rješenje unutar zadane preciznosti
               return t;  
                                         
            } else if (usp < 0) {
              // rješenje je u gornjoj polovici intervala
              s = t;      
             
            } else {
              // rješenje je u donjoj polovici intervala
              e = t ;
             
            }
     }
     return t;    
}
 
 
// k-ti korijen, moramo drzati globalno zbog prototipa funkcije usporedbe
unsigned int k = 2;
 
// callback funkcija za usporedbu, racunamo (t^k - n)
real razlika(real t, real n) {
     real potencija = 1;
     for (int i = 0; i < k; i++) potencija *= t;
     return (potencija - n);
}
 
 
 
// funkcija koja racuna korijen iz N po zadanom stupnju korijenovanja
real korijen (real n, int stupanj) {
     // binarano pretrazi interval [1,n] s preciznoscu preciznost
     // --> trazi korijen od n po callback funkciji za usporedbu "razlika"
     // postavi stupanj korijenovana globalno
     k = stupanj;
     return binarno(1,n,preciznost,n,razlika);
}
 
 
int main() {
 
    real n;
    unsigned int stupanj;
    // n je broj pod korijenom, stupanj je stupanj korijenovanja (stupanj >= 2)
    cin >> n >> stupanj;
 
    // pozovi funkciju za korijen i ispisi rezultat
    cout <<  korijen(n,stupanj) << endl;
 
    system("pause");
    return 0;
}