/*
   Primjer: Vektori + funkcije + procedure + ByRef prijenos parametara
        
            Unosimo niz od N cijelih brojeva, ispisujemo novi niz gdje
            je svaki element originala udvostručen, zatim ispisujemo originalni
            niz. Rabimo vlastite (korisničke) pomoćne procedure i funkcije.

   Složenost: Linearna za sve operacije nad nizovima izuzev prijenosa u proc.
        
   Autor: Kristijan Burnik, Udruga informatičara Božo Težak
          Gmail: kristijanburnik
   
   Datum: 20.02.2012.

*/
#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>

using namespace std;

// definiramo novi tip, kasnije lakše promijenimo u float ili drugi tip!
// isto je praktičnije i kraće pisati samo "VI"
typedef vector <int> VI;

// unosimo vektor sa std ulaza, vektor mora biti resizean kako bi ovo radilo!
void unesi(VI &v) {
    // buduci v prenosimo kao &v, odnosno kao referencu (By Reference),
    // to znaci da ce v biti promijenjen u pozivatelju (npr. main-u)! 
    // Usputno, ByRef je brzi, jer nema potrebe za kopiranjem cijelog vektora!
    for (int i = 0 ; i < v.size() ; i++) cin >> v[i];
}

// ispisujemo vektor na std izlaz, prenosimo ByRef radi brzine 
// "ispisi" je read-only nad vektorom v!
void ispisi(VI &v) {
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
}

// svaki element mnozimo s dva, ali vracamo novi vektor, original je read-only
VI dupliraj(VI &v) {
    VI out;
    for(int i = 0; i < v.size(); i++) out.push_back(v[i]*2);
    return out;
}


int main() {    
    int n; 
    cin >> n;
    
    // obavezno resizeamo vektor! Jer smo tako predvidjeli rad procedure "unesi"
    VI v;
    v.resize(n);
    
    // popuni vektor ulazima (ocekujemo n brojeva na ulazu)
    unesi(v);
    
    // napravi novi "duplirani" vektor
    VI out = dupliraj(v);
    
    // ispisi duplirani vektor
    ispisi(out);
    
    // ispisi originalni vektor
    ispisi(v);
    
    // system("pause");
    return 0;
}