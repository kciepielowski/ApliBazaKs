#include "akcja.h"
#include "sharedtypes.h"
#include <QMessageBox>

void Akcja::on_tablica_click(int clickedRow, int clickedColumn)
{
QTableWidget* snd=qobject_cast<QTableWidget*>(sender());
    paramText=tablica[id].parametr;
    param2Text=snd->item(clickedRow,clickedColumn)->text();
    wynik=tablica[id].wynik;
    if(tablica[id].fn==SQL)
    {
        sql();
    }

}
void Akcja::on_przycisk_click(int id)
{
    paramText=przyciski[id].parametr;
    wynik=przyciski[id].wynik;
    QMessageBox msgBox;
    switch (przyciski[id].fn)
    {
    case ZAMKNIJ:
        zamknij();
        break;
    case WYWOLAJ:
        wywolaj();
        break;
    case SQL:
        sql();
        break;
    case POLICZ:
        policz();
        break;
       default:
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Nie obsłużona funkcja."));
        msgBox.exec();
        break;
    }
}
void Akcja::zamknij()
{
    parentWindow->close();
}


void Akcja::wywolaj()
{
    int result;
    QString loginfo=" ";
    QMessageBox msgBox;
    if(paramText.toLower().contains(".xml"))
    {
        if(!baza.User.isEmpty())loginfo+=baza.User;
        if(!baza.Password.isEmpty())loginfo+=" "+baza.Password;
        if(loginfo==" ")loginfo="";
#ifdef Q_WS_X11
        result=system(programName.toAscii()+" "+paramText.toAscii()+loginfo.toAscii());
#endif
#ifdef Q_WS_WIN
        result=system(programName.toAscii()+" "+paramText.toAscii()+loginfo.toAscii());
#endif
    }else result=system(paramText.toAscii());
        if(result!=0){
             msgBox.setIcon(QMessageBox::Warning);
             msgBox.setText(tr("Błąd funkcji wywołaj."));
             msgBox.exec();
        }

}
void Akcja::policz()
{
    QScriptEngine myEngine;
    QScriptValue result;
    int8_t resultFieldNumber=0;
    Elementy resultType;
    for(int i=0;i<objectCounter.poleTekst;i++)
    {
        paramText.replace(poleTekst[i].ident,polaTekstowe[i]->text());
        if(poleTekst[i].ident==wynik)
        {
            resultFieldNumber=i;
            resultType=POLETEKST;
        };
    }
    for(int i=0;i<objectCounter.pole;i++)
    {
        paramText.replace(pole[i].ident,pole[i].tekst);
        if(pole[i].ident==wynik)
        {
            resultFieldNumber=i;
            resultType=POLE;
        };
    }
    paramText.replace(",",".");
    result = myEngine.evaluate(paramText);
    if(resultType==POLETEKST)polaTekstowe[resultFieldNumber]->setText(result.toString());
    if(resultType==POLE)pola[resultFieldNumber]->setText(result.toString());
}
void Akcja::sql()
{

    QString fieldId;
    int8_t resultFieldCount;
    int8_t resultPos[15][2],resultI=0;
    Elementy resultFieldType[15];
    QStringList kolumny;
    resultFieldCount=wynik.count(';')+1;
     resultFieldType[0]=PUSTE;
     wynik.split(';').at(resultI);
     for(int i=0;i<objectCounter.poleTekst;i++)
     {
         fieldId=":"+poleTekst[i].ident;
         paramText.replace(fieldId,polaTekstowe[i]->text());
         if(wynik.contains(';'))
         for(int j=0;j<resultFieldCount;j++)
             if(poleTekst[i].ident==wynik.split(';').at(j)){
             resultPos[0][resultI]=i;resultPos[1][resultI]=j;
             resultFieldType[resultI++]=POLETEKST;}
     }
     for(int i=0;i<objectCounter.pole;i++)
     {
         fieldId=":"+pole[i].ident;
         paramText.replace(fieldId,pole[i].tekst);
                 for(int j=0;j<resultFieldCount;j++)
                     if(pole[i].ident==wynik.split(';').at(j)){
                     resultPos[0][resultI]=i;resultPos[1][resultI]=j;
                     resultFieldType[resultI++]=POLE;}
     }
     for(int i=0;i<objectCounter.tablica;i++)
     {
          fieldId=":"+tablica[id].ident;
          paramText.replace(fieldId,param2Text);
       for(int j=0;j<resultFieldCount;j++)
           if(tablica[i].ident==wynik.split(';').at(j)){
                     resultPos[0][resultI]=i;resultPos[1][resultI]=j;
                     resultFieldType[resultI++]=TABLICA;};
     }
     query=db.exec(paramText);
     for(int i=0;i<resultI;i++)
     {
     if(resultFieldType[i]==POLETEKST){
         query.seek(0);
         polaTekstowe[resultPos[0][i]]->setText(query.value(resultPos[1][i]).toString());
     }else if(resultFieldType[i]==POLE){
         query.seek(0);
         pole[resultPos[0][i]].tekst=query.value(resultPos[1][i]).toString();
     }else if(resultFieldType[i]==TABLICA){
         int8_t row,column;
         row=0;
         query.seek(0);
         tablice[resultPos[0][i]]->setColumnCount(0);
         tablice[resultPos[0][i]]->setRowCount(0);
        do
        {

             tablice[resultPos[0][i]]->insertRow(row);
             column=0;
             while(query.value(column).isValid())
                           {
                if(tablice[resultPos[0][i]]->columnCount()<column+1)tablice[resultPos[0][i]]->insertColumn(column);
                if(row==0)kolumny.append(query.record().fieldName(column));
                itemPointer=new QTableWidgetItem(query.value(column).toString());
                tablice[resultPos[0][i]]->setItem(row, column++, itemPointer);
                         }
             row++;
         } while(query.next());
         tablice[resultPos[0][i]]->setHorizontalHeaderLabels(kolumny);
     }
     }
}
