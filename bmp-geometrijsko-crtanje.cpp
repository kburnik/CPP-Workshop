/*
    Tema: Crtanje geometrijskih likova - proceduralna paradigma
   
      U ovom primjeru ostvarujemo "framework", odnosno vlastito okružje kao
      skup alata i metoda za rad s geometrijskim likovima.
      U prvom dijelu radimo isključivo s osnovnim tipovima podataka
      (bez struktura), a potom (u drugom primjeru) to isto ostvarujemo
      rabeći strukture kako bi naglasili prednosti tog pristupa
      implementaciji.
     
      Kao primjer uporabe ovog okružja, ostvarujemo crtanje nekoliko
      kružnica, linija i pravokutnika.
     
      Crtanje ćemo ostvariti kao generiranje bitmape (matrice točaka,
      tj. boja) koju kasnije možemo otvoriti u nekom grafičkom pregledniku.
     
      U ovoj implementaciji svakako treba uočiti da je bilo kakva manipulacija
      "objektima" u smislu vektorske grafike gotovo nezamisliva, a u najmanju
      ruku jako nezgrapna - takav rad bi se svodio na vođenje računa o jako
      velikom broju nepovezanih (negrupiranih) varijabli. Također i metode
      kojima bi manipulaciju (npr. skaliranje ili rotaciju) ostvarili bile
      bi isto tako nezgrapne i tražile velik broj parametara. U tom smislu
      bilo kakva objektna paradigma (objektno orijentirani dizajn), pa čak
      i onaj s jednostavnim strukturama, mnogo pojednostavljuje rad s ovim
      "objektima".
 
    Datum: 06.10.2012.
 
    Autor: Kristijan Burnik, udruga informatičara Božo Težak
 
    Gmail: kristijanburnik
 
*/
 
#include <iostream>
#include <cstdlib>
#include <cmath>
 
using namespace std;
 
// tri byte-a su potrebna za ostvarenje RGB tehnike bojanja (16 milijuna boja)
// često ćemo to rabiti pa ovdje radimo kraticu
// R,G,B su u intervalu [0,255]
typedef unsigned char byte;
 
 
// definiramo neke konstante koje ćemo često rabiti,
// zgodno nam je imati neka svojstva definirana na jednom mjestu
// kako bi ih kasnije lako modificirali po potrebi ili učinili fleksibilnijima
// dodatnom implementacijom (npr. proizvoljni unos dimenzija bitmape)
const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;
 
// definiramo kojim redom su poslagane boje, da ne bismo pomiješali indekse
// ovo je jedan manji primjer tzv. "defenzivnog programiranja"
// -> unaprijed spriječavamo moguće pogreške
const int R = 0;
const int G = 1;
const int B = 2;
 
// bitmapa je ovdje matrica dimenzija 1024x768 i dodatne tri vrijednosti
// na svakom polju za boju, ovo je najopćenitiji oblik zapisa bitmape
// koji kasnije rabimo kod generiranja izlazne BMP datoteke
byte bitmap[ BITMAP_WIDTH ][ BITMAP_HEIGHT ][ 3 ];
 
 
// metoda za postavljanje jednog pixela u zadanu boju
// rabi se u svim ostalim dijelovima za renderiranje (čitaj: produciranje slike)
void setpixel(int x,int y,int r,int g,int b) {
    bitmap[x][y][R] = r;
    bitmap[x][y][G] = g;            
    bitmap[x][y][B] = b;
}
 
// metoda za postavljanje čitave bitmape u zadanu boju
void clearbitmap(byte r, byte g, byte b)  {
    for (int i = 0; i < BITMAP_WIDTH; i++ ) {
        for (int j = 0; j < BITMAP_HEIGHT; j++ ) {
           setpixel(i,j,r,g,b) ;
        }  
    }
}
 
// metoda za crtanje linije, zapravo to je pravac kroz dvije točke u nekom
// intervalu [x1,x2]
// metoda nije baš "najfinija", treba se još doraditi da linija izgleda glađe
// za neke nagibe
void line(int x1,int y1, int x2,int y2, byte r, byte g, byte b) {
    // jednadzba pravca kroz dvije točke glasi:
    // (x2 - x1)*(y - y1) = (y2 - y1)*(x - x1)
    // kako ne bi tražili po citavoj matrici
    // ograničavamo se na opisani pravokutnik
    int sx = min(x1,x2);
    int ex = max(x1,x2);
    int sy = min(y1,y2);
    int ey = max(y1,y2);
   
   
    float dx = x2 - x1;
    float dy = y2 - y1;
 
    float dif = 1.f;
    if (dx == 0) {
        for (int y = sy; y <= ey; y++) {
                 setpixel((int)sx,y,r,g,b);    
        }
    } else if (dy == 0) {
        for (int x = sx; x <= ex; x++) {
                 setpixel(x,sy,r,g,b);    
        }
    } else {
        for (float x = sx; x <= ex; x+= dif) {
                 float  y = y1 + (dy) * (x - x1)/(dx);
                 setpixel((int)x,(int)y,r,g,b);
        }
    }
   
}
 
// pravokutnik je zadan s dva vrha (dijagonalom) i željenom bojom
// isto kao i linija
void rectangle(int x1,int y1, int x2,int y2, byte r, byte g, byte b) {
    // normaliziramo točke kako bi dijagonalu mogli zadati na bilo koji način
    if (x1 > x2) swap(x1,x2);
    if (y1 > y2) swap(y1,y2);
   
    // crtamo redom linije spajajući točke:
    /// NW,NE,SE,SW (orijentacija po stranama svijeta)
    line(x1,y1,x2,y1,r,g,b);
    line(x2,y1,x2,y2,r,g,b);
    line(x2,y2,x1,y2,r,g,b);
    line(x1,y2,x1,y1,r,g,b);
   
    // uočiti da smo složeniji "objekt" pravokutnik sastavili od linija
    // a linije od točaka! ovo je česta pojava koju
    // posebice u objektnoj paradigmi susrećemo gotovo na svakom koraku
   
}
 
 
// metoda za crtanje kružnice
// za nju su potrebe koordinate središta, radijus i boja
// metoda također nije "najfinija", tj. dade se doraditi i pojednostavniti
// druga, ponešto sporija metoda bi bila upotrebom trigonometrijskih funkcija
// sinus i/ili kosinus, međutim ovo je svakako dovoljno za jednostavan prikaz
void circle(int sx, int sy, int radius, byte r, byte g, byte b) {
    // jednadžba kružnice glasi (x - sx)^2 + (y - sy)^2 = r
    // da ne trazimo po čitavoj matrici ograničavamo se na opisani joj kvadrat
    float rr = radius*radius;
    for (float x = sx - radius - 1; x <= sx + radius + 1; x+=1 ) {
        for (float y = sy - radius - 1; y <= sy + radius +1 ; y+=1) {
            int xsx = (int)(x - sx);
            int ysy  = (int)(y - sy);
            if ( abs((xsx*xsx + ysy*ysy) - rr) <= radius)  {
               setpixel((int)x,(int)y,r,g,b);
            }
        }
    }
}
 
 
// metoda za spremanje bitmape, zanemariti implementaciju jer je manje važna
// više o strukturi bitmap datoteka:
//    http://en.wikipedia.org/wiki/BMP_file_format
// ova implementacija konkretno ima problema sa ispravnim prikazom boja
// međutim postoji niz bibiloteka koje nam mogu poslužiti za renderiranje BMP-a
// s puno većom pouzdanošću i potrebnim opcijama
// ova implementacija je prilagođena, a preuzeta je izvorno sa adrese :
//    http://stackoverflow.com/a/2654860
void outputbitmap(string filename = "img.bmp") {
   
    int w = BITMAP_WIDTH;
    int h = BITMAP_HEIGHT;
   
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*w*h;
    if( img )
        free( img );
    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,sizeof(img));
   
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
    {
        int x=i; int y=j;
        int r = bitmap[i][j][R]*255;
        int g = bitmap[i][j][G]*255;
        int b = bitmap[i][j][B]*255;
        if (r > 255) r=255;
        if (g > 255) g=255;
        if (b > 255) b=255;
        img[(x+y*w)*3+2] = (unsigned char)(r);
        img[(x+y*w)*3+1] = (unsigned char)(g);
        img[(x+y*w)*3+0] = (unsigned char)(b);
    }
    }
   
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};
   
    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
   
    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);
   
    f = fopen(filename.c_str(),"wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
    fclose(f);    
}
 
 
// glavni program koji rabi naš "framework"
// i obavlja pripremu, crtanje te rendering
// čistimo bitmapu i crtamo nekoliko geometrijskih "likova" (objekata)
int main() {
   
    clearbitmap(255,255,255);
 
    line (10,10,400,200,  100,0,0);
    rectangle(10,10,400,200  ,0,100,0);
       
    circle(450,450,150, 0,0,100);
 
    // spremamo bitmapu
    outputbitmap( "img.bmp" );
   
    cout << "Generirana bitmapa se nalazi u istom direktoriju programa."
         << endl
         << "Pod nazivom \"img.bmp\""
         << endl
         << endl
    ;
     
    system("pause");
 
    return 0;
}