/*
    Zadatak: Permutacija 6 elemenata
 
    Datum: 2012-12-01
 
    Autor: Kristijan Burnik, udruga informatičara Božo Težak
 
    Gmail: kristijanburnik
 
*/
#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int main(void) {
 
    int a[6];
    for (int i = 0 ; i < 6; i++)
        cin >> a[i];
       
   
    for (int i = 0 ; i < 6; i++){
        for (int j = 0 ; j < 6; j++){
            if (j != i) {
                for (int k = 0 ; k < 6; k++){
                    if (k != i && k != j) {
                        for (int l = 0; l < 6; l++) {
                            if (l != i && l!= j && l != k ) {
                                for (int m = 0; m < 6; m++) {
                                    if (m != i && m!=j && m != k && m != l) {
                                        for (int n = 0; n < 6; n++) {
                                            if (n != i && n!=j && n != k && n != l && n != m) {
                                                cout
                                                    << a[i] << " "
                                                    << a[j] << " "
                                                    << a[k] << " "
                                                    << a[l] << " "
                                                    << a[m] << " "
                                                    << a[n] << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }  
    }
 
 
    system("pause");
    return 0;
}