/*
    Zadatak: Permutacija 3 elementa
 
    Datum: 2012-12-01
 
    Autor: Kristijan Burnik, udruga informatičara Božo Težak
 
    Gmail: kristijanburnik
 
*/
#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int main(void) {
 
    int a[3];
    for (int i = 0 ; i < 3; i++)
        cin >> a[i];
       
   
    for (int i = 0 ; i < 3; i++){
        for (int j = 0 ; j < 3; j++){
            if (j != i) {
                for (int k = 0 ; k < 3; k++){
                    if (k != j && k != i) {
                        cout
                            << a[i] << " "
                            << a[j] << " "
                            << a[k] << endl;    
                    }
                }
            }
        }  
    }
 
 
 
    system("pause");
    return 0;
}