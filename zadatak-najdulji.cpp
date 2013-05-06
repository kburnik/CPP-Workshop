// program NADJULJI :: najdulji najkasniji zajednicki dio niza
#include <iostream>
 
using namespace std;
 
int main() {
    char s[100],q[100];
   
    gets(s);
    gets(q);
 
    int lens = strlen(s);
    int lenq = strlen(q);
    int length = 0,start=0;
    for (int i = 0; i < lens; i++) {
        int j = 0;
        while (j < lenq) {
            int k = i;
            int c = 0;
            while (s[k] == q[j]) {
              k++;
              j++;
              c++;
              if (c >= length) {
                start = i;
                length = c;
              }
            }
            j++;
       }
    }
 
    // onaj koji se pojavljuje poslije!!
    s[start+length] = 0;
    puts(s+start);
 
 
    system("pause");
    return 0;
}