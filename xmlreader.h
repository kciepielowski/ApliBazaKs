#ifndef XMLREADER_H
#define XMLREADER_H
#include <QXmlStreamReader>
#include <QFile>
#include "sharedtypes.h"

class XMLReader: public QXmlStreamReader
{
    private:
    IloscObiektow *obCount;
public:
    int8_t elem=0;
    XMLReader(QFile* f, IloscObiektow* c);

    bool isNameEqual(QString str);
    bool isFunkcjaEqual(QString str);
    Elementy readTypeOfElement();
    QString getStringAttribute(QString str);
    int8_t getIntAttribute(QString str);
    void ifInTablica(Obiekt* ob);
    void readConstPart(Obiekt* ob);
    void readFunkcja(Przycisk* ob);
    void readObiekt(Obiekt* ob);
    void readPrzycisk(Przycisk* ob);
    void readTablica(Tablice* ob);

    /*
      if(akt_tablica){
                    tekst[objectCounter.tekst].tablica=objectCounter.tablica-1;
                    tekst[objectCounter.tekst].wiersz=tablica[objectCounter.tablica-1].wiersze-1;
                    tekst[objectCounter.tekst].kolumna=elem;
                }
                ++objectCounter.tekst;
                if(akt_wiersz)++elem;
     */

};
#endif // XMLREADER_H
