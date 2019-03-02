#ifndef OBJECTS
#define OBJECTS
#include "QString"
enum funkcja{BRAK=0, ZAMKNIJ=1, POLICZ=2, WYWOLAJ=4, SQL=5};
enum Elementy {OKNO=0,TYTUL=1,TEKST=2,POLETEKST=3,PRZYCISK=4, TABLICA=5, WR=6, POLE=7, PUSTE=99};
class IloscObiektow
{
public:
    int8_t tekst=0;
    int8_t poleTekst=0;
    int8_t przyciski=0;
    int8_t tablica=0;
    int8_t pole=0;
};
class Obiekt
{
public:
    QString tekst;
    QString ident;
    int8_t wiersz;
    int8_t kolumna;
    int8_t pwiersz;
    int8_t pkolumna;
    int8_t tablica;
    Obiekt(){pwiersz=1;pkolumna=1;}
};
class Przycisk: public Obiekt
{
public:
    funkcja fn;
    QString parametr;
    QString wynik;
};
class Tablice: public Przycisk
{
public:
    int8_t wiersze;
    int8_t kolumny;
};
#endif // OBJECTS

