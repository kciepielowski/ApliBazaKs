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
   return (QXmlStreamReader::attributes().value("funkcja").toString()==str);
}
Elementy XMLReader::readTypeOfElement()
{
    if(isNameEqual("tytul"))return TYTUL;
    else if(isNameEqual("okno"))return OKNO;
    else if(isNameEqual("tekst"))return TEKST;
    else if(isNameEqual("poletekst"))return POLETEKST;
    else if(isNameEqual("przycisk"))return PRZYCISK;
    else if(isNameEqual("tablica"))return TABLICA;
    else if(isNameEqual("wr"))return WR;
    else if(isNameEqual("pole"))return POLE;
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
    ob->wiersz=getIntAttribute("wiersz");
    ob->kolumna=getIntAttribute("kolumna");
    if(!attributes().value("pwiersz").isEmpty())
        ob->pwiersz=getIntAttribute("pwiersz");
    if(!attributes().value("pkolumna").isEmpty())
        ob->pkolumna=getIntAttribute("pkolumna");
    ob->ident=getStringAttribute("id");
    ob->tablica=99;
}
void XMLReader::readFunkcja(Przycisk* ob)
{
    if(isFunkcjaEqual("zamknij"))ob->fn=ZAMKNIJ;
    else if(isFunkcjaEqual("policz"))ob->fn=POLICZ;
    else if(isFunkcjaEqual("wywolaj"))ob->fn=WYWOLAJ;
    else if(isFunkcjaEqual("sql"))ob->fn=SQL;
    ob->parametr=getStringAttribute("param");
    ob->wynik=getStringAttribute("wynik");
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
