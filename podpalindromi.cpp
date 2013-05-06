#include <iostream>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
// popis palindroma spremamo globalno
vector < string > palindromi;
 
// niz je palindrom ako se jednako cita s obje strane i duljine >= 2
bool palindrom(string s) {
     int len = s.size();
     // idemo do cjelobrojne polovice
     for (int i = 0 ; i < len/2 ; i++) {
         // ako se nasuprotni elementi ne poklapaju, niz nije palindrom
         if (s[i] != s[len-i-1])
            return false;
     }
     // niz je palindrom ako je duljine barem 2
     return s.size() > 1;
}
 
 
// obrada: ako je s palindrom, dodaj ga na popis palindroma
void obradi(string s) {    
     if (palindrom(s)) palindromi.push_back(s);
}
 
// kriterij usporedbe: prvo po duljini, zatim leksikografski
int cmp (string a, string b){
    if (a.size() == b.size())
       return a < b;
       
    return a.size() < b.size();  
}
 
int main () {
   
    string s;
    cin >> s;
   
    // duljina niza
    int len = s.size();
   
    // generiraj sve podnizove
    for (int i = 0 ; i < len; i++) {
        for (int j = 1; j <= (len - i) ; j++) {
            // obradi pojedini podniz
            obradi( s.substr(i,j) );
        }
    }
 
    // sortiraj popis palindroma po kriteriju duljine, zatim leksikografski
    sort( palindromi.begin(), palindromi.end(), cmp );
   
    // ispisi sortirani popis palindroma
    for (int i  = 0 ; i < palindromi.size(); i++) {
        cout << palindromi[i] << endl;
    }
 
    system ("pause");
    return 0;
}