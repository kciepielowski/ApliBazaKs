#include "xmlreader.h"

XMLReader::XMLReader(QFile* f, IloscObiektow* c):QXmlStreamReader{f}
{
    obCount=c;
}
bool XMLReader::isNameEqual(QString str)
{
   return (QXmlStreamReader::name().toString().toLower()==str);
}
bool XMLReader::isFunkcjaEqual(QString str)
{
   return (QXmlStreamReader::attributes().value(QObject::tr("funkcja")).toString()==str);
}
Elementy XMLReader::readTypeOfElement()
{
    if(isNameEqual(QObject::tr("tytul")))return TYTUL;
    else if(isNameEqual(QObject::tr("okno")))return OKNO;
    else if(isNameEqual(QObject::tr("tekst")))return TEKST;
    else if(isNameEqual(QObject::tr("poletekst")))return POLETEKST;
    else if(isNameEqual(QObject::tr("przycisk")))return PRZYCISK;
    else if(isNameEqual(QObject::tr("tablica")))return TABLICA;
    else if(isNameEqual(QObject::tr("wr")))return WR;
    else if(isNameEqual(QObject::tr("pole")))return POLE;
    return PUSTE;
}

QString XMLReader::getStringAttribute(QString str)
{
    return attributes().value(str).toString();
}

int8_t XMLReader::getIntAttribute(QString str)
{
    return attributes().value(str).toString().toInt();
}
void XMLReader::readConstPart(Obiekt* ob)
{
    ob->wiersz=getIntAttribute(QObject::tr("wiersz"));
    ob->kolumna=getIntAttribute(QObject::tr("kolumna"));
    if(!attributes().value(QObject::tr("pwiersz")).isEmpty())
        ob->pwiersz=getIntAttribute(QObject::tr("pwiersz"));
    if(!attributes().value(QObject::tr("pkolumna")).isEmpty())
        ob->pkolumna=getIntAttribute(QObject::tr("pkolumna"));
    ob->ident=getStringAttribute(QObject::tr("id"));
    ob->tablica=99;
}
void XMLReader::readFunkcja(Przycisk* ob)
{
    if(isFunkcjaEqual(QObject::tr("zamknij")))ob->fn=ZAMKNIJ;
    else if(isFunkcjaEqual(QObject::tr("policz")))ob->fn=POLICZ;
    else if(isFunkcjaEqual(QObject::tr("wywolaj")))ob->fn=WYWOLAJ;
    else if(isFunkcjaEqual(QObject::tr("sql")))ob->fn=SQL;
    ob->parametr=getStringAttribute(QObject::tr("param"));
    ob->wynik=getStringAttribute(QObject::tr("wynik"));
}

void XMLReader::readObiekt(Obiekt* ob){
    readConstPart(ob);
    ob->tekst=readElementText();
    ifInTablica(ob);
}
void XMLReader::readPrzycisk(Przycisk* ob){
    readConstPart(ob);
    readFunkcja(ob);
    ob->tekst=readElementText();
    ifInTablica(ob);
}
void XMLReader::readTablica(Tablice* ob){
    readConstPart(ob);
    ob->wiersze=0;
    ob->kolumny=0;
    readFunkcja(ob);
    akt_tablica=true;
}
void XMLReader::ifInTablica(Obiekt* ob)
{
  if(akt_tablica){
                ob->tablica=objectCounter.tablica-1;
                ob->wiersz=tablica[objectCounter.tablica-1].wiersze-1;
                ob->kolumna=elem;
            }
            if(akt_wiersz)++elem;
}
