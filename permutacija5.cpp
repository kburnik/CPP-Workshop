/*
    Zadatak: Permutacija 5 elemenata
 
    Datum: 2012-12-01
 
    Autor: Kristijan Burnik, udruga informatičara Božo Težak
 
    Gmail: kristijanburnik
 
*/
#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int main(void) {
 
    int a[5];
    for (int i = 0 ; i < 5; i++)
        cin >> a[i];
       
   
    for (int i = 0 ; i < 5; i++){
        for (int j = 0 ; j < 5; j++){
            if (j != i) {
                for (int k = 0 ; k < 5; k++){
                    if (k != i && k != j) {
                        for (int l = 0; l < 5; l++) {
                            if (l != i && l!= j && l != k ) {
                                for (int m = 0; m < 5; m++) {
                                    if (m != i && m!=j && m != k && m != l) {
                                        cout
                                            << a[i] << " "
                                            << a[j] << " "
                                            << a[k] << " "
                                            << a[l] << " "
                                            << a[m] << endl;    
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