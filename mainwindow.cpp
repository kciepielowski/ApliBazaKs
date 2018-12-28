#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtScript/QScriptEngine>
#include "baza.h"
//#include <QTime>
//QTime j;
//QString plik;

QString wysokosc,szerokosc, tytul;
ilObiektow il;
QLineEdit *polaTekstowe[15];
QTableWidget *tablice[5];
Obiekt Tekst[15], pole_Tekst[15], Pole[15];
Tablice Tablica[5];
Przycisk przyciski[15];
Baza baza;
QTableWidgetItem *Items;
//QTableWidgetItem *newItem;

bool akt_wiersz, akt_tablica;
int wiersz, kolumna, pwiersz, pkolumna;

void Odczytaj_XML(const QString &fileName) {
    enum Elementy {OKNO=0,TYTUL=1,TEKST=2,POLETEKST=3,PRZYCISK=4, TABLICA=5, WR=6, POLE=7, BRAK=99};
    Elementy Element;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
int8_t elem=0;
    QXmlStreamReader reader(&file);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if(reader.name().toString().toLower()=="tytul")Element=TYTUL;
            else if(reader.name().toString().toLower()=="okno")Element=OKNO;
            else if(reader.name().toString().toLower()=="tekst")Element=TEKST;
            else if(reader.name().toString().toLower()=="poletekst")Element=POLETEKST;
            else if(reader.name().toString().toLower()=="przycisk")Element=PRZYCISK;
            else if(reader.name().toString().toLower()=="tablica")Element=TABLICA;
            else if(reader.name().toString().toLower()=="wr")Element=WR;
            else if(reader.name().toString().toLower()=="pole")Element=POLE;
            else Element=BRAK;
            switch(Element)
            {
             case TYTUL:
                tytul = reader.readElementText();
             break;
             case OKNO:
                wysokosc=reader.attributes().value("w").toString();
                szerokosc=reader.attributes().value("s").toString();
             break;
             case TEKST:
                Tekst[il.Tekst].wiersz=reader.attributes().value("wiersz").toString().toInt();
                Tekst[il.Tekst].kolumna=reader.attributes().value("kolumna").toString().toInt();                
                if(!reader.attributes().value("pwiersz").isEmpty())Tekst[il.Tekst].pwiersz=reader.attributes().value("pwiersz").toString().toInt();
                if(!reader.attributes().value("pkolumna").isEmpty())Tekst[il.Tekst].pkolumna=reader.attributes().value("pkolumna").toString().toInt();
                Tekst[il.Tekst].ident=reader.attributes().value("id").toString();
                Tekst[il.Tekst].tekst=reader.readElementText();
                Tekst[il.Tekst].tablica=99;
                if(akt_tablica){
                    Tekst[il.Tekst].tablica=il.tablica-1;
                    Tekst[il.Tekst].wiersz=Tablica[il.tablica-1].wiersze-1;
                    Tekst[il.Tekst].kolumna=elem;
                }
                ++il.Tekst;
                if(akt_wiersz)++elem;
             break;
             case POLETEKST:
                pole_Tekst[il.pole_Tekst].wiersz=reader.attributes().value("wiersz").toString().toInt();
                pole_Tekst[il.pole_Tekst].kolumna=reader.attributes().value("kolumna").toString().toInt();
                if(!reader.attributes().value("pwiersz").isEmpty())pole_Tekst[il.pole_Tekst].pwiersz=reader.attributes().value("pwiersz").toString().toInt();
                if(!reader.attributes().value("pkolumna").isEmpty())pole_Tekst[il.pole_Tekst].pkolumna=reader.attributes().value("pkolumna").toString().toInt();
                pole_Tekst[il.pole_Tekst].ident=reader.attributes().value("id").toString();
                pole_Tekst[il.pole_Tekst].tekst=reader.readElementText();
                pole_Tekst[il.pole_Tekst].tablica=99;
                if(akt_tablica){
                    pole_Tekst[il.pole_Tekst].tablica=il.tablica-1;
                    pole_Tekst[il.pole_Tekst].wiersz=Tablica[il.tablica-1].wiersze-1;
                    pole_Tekst[il.pole_Tekst].kolumna=elem;
                }
                ++il.pole_Tekst;
                if(akt_wiersz)++elem;
             break;
            case TABLICA:
               Tablica[il.tablica].wiersz=reader.attributes().value("wiersz").toString().toInt();
               Tablica[il.tablica].kolumna=reader.attributes().value("kolumna").toString().toInt();
               if(!reader.attributes().value("pwiersz").isEmpty())Tablica[il.tablica].pwiersz=reader.attributes().value("pwiersz").toString().toInt();
               if(!reader.attributes().value("pkolumna").isEmpty())Tablica[il.tablica].pkolumna=reader.attributes().value("pkolumna").toString().toInt();
               Tablica[il.tablica].ident=reader.attributes().value("id").toString();
               Tablica[il.tablica].tablica=99;
               Tablica[il.tablica].wiersze=0;
               Tablica[il.tablica].kolumny=0;
               przyciski[il.przyciski].tablica=99;
               //if(akt_tablica){
               //    Tablica[il.tablica].tablica=il.tablica-1;
               //    Tablica[il.tablica].wiersz=Tablica[il.tablica-1].wiersze-1;
               //    Tablica[il.tablica].kolumna=elem;
               //}
               ++il.tablica;
               akt_tablica=true;
            break;
            case WR:
              akt_wiersz=true;
               ++Tablica[il.tablica-1].wiersze;
            break;
            case POLE:
               Pole[il.pole].wiersz=reader.attributes().value("wiersz").toString().toInt();
               Pole[il.pole].kolumna=reader.attributes().value("kolumna").toString().toInt();
               Pole[il.pole].ident=reader.attributes().value("id").toString();
               Pole[il.pole].tekst=reader.readElementText();
               Pole[il.pole].tablica=99;
               if(akt_tablica){
                   Pole[il.pole].tablica=il.tablica-1;
                   Pole[il.pole].wiersz=Tablica[il.tablica-1].wiersze-1;
                   Pole[il.pole].kolumna=elem;
               }
               ++il.pole;
               if(akt_wiersz)++elem;
            break;
             case PRZYCISK:
                przyciski[il.przyciski].wiersz=reader.attributes().value("wiersz").toString().toInt();
                przyciski[il.przyciski].kolumna=reader.attributes().value("kolumna").toString().toInt();
                if(!reader.attributes().value("pwiersz").isEmpty())przyciski[il.przyciski].pwiersz=reader.attributes().value("pwiersz").toString().toInt();
                if(!reader.attributes().value("pkolumna").isEmpty())przyciski[il.przyciski].pkolumna=reader.attributes().value("pkolumna").toString().toInt();
                przyciski[il.przyciski].ident=reader.attributes().value("id").toString();
                if(reader.attributes().value("funkcja").toString()=="zamknij")przyciski[il.przyciski].fn=ZAMKNIJ;
                else if(reader.attributes().value("funkcja").toString()=="policz")przyciski[il.przyciski].fn=POLICZ;
                else if(reader.attributes().value("funkcja").toString()=="wywolaj")przyciski[il.przyciski].fn=WYWOLAJ;
                else if(reader.attributes().value("funkcja").toString()=="sql")przyciski[il.przyciski].fn=SQL;
                przyciski[il.przyciski].parametr=reader.attributes().value("param").toString();
                przyciski[il.przyciski].wynik=reader.attributes().value("wynik").toString();
                przyciski[il.przyciski].tekst=reader.readElementText();
                przyciski[il.przyciski].tablica=99;
                if(akt_tablica){
                    przyciski[il.przyciski].tablica=il.tablica-1;
                    przyciski[il.przyciski].wiersz=Tablica[il.tablica-1].wiersze-1;
                    przyciski[il.przyciski].kolumna=elem;
                }
                ++il.przyciski;
                if(akt_wiersz)++elem;
             break;
               default:
                break;
            }
        }
        if (reader.isEndElement())
        {
         if(reader.name().toString().toLower()=="tablica")
         {
             akt_tablica=false;
         }
         if(reader.name().toString().toLower()=="wr")
         {
           akt_wiersz=false;
           if(Tablica[il.tablica-1].kolumny<elem)Tablica[il.tablica-1].kolumny=elem;
           elem=0;
         }
        }

    }

    if (reader.hasError()) {
        return;
    }
}

void Odczytaj_XMLBaza(const QString &fileName) {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QXmlStreamReader reader(&file);

    while (!reader.atEnd()){
        reader.readNext();
       if (reader.isStartElement()) {
            if(reader.name().toString().toLower()=="typ")
                baza.Typ = reader.readElementText().toUpper();
            if(reader.name().toString().toLower()=="nazwa")
                baza.Nazwa = reader.readElementText().toLower();
            if(reader.name().toString().toLower()=="host")
                baza.Host = reader.readElementText();
            if(reader.name().toString().toLower()=="port")
                baza.Port = reader.readElementText().toInt();
       }
      }


    if (reader.hasError()) {
        return;
    }
}

void MainWindow::on_przycisk_klik(int id)
{
    QString x,ident;
    int8_t w,k,ile=1;
    int8_t nidw[15],idw[15],typ_idw[15],zz=0;
    QScriptEngine myEngine;
    QScriptValue x2;
    QStringList kolumny;
    x=przyciski[id].parametr;
    switch (przyciski[id].fn)
    {
    case ZAMKNIJ:
        close();
        break;
    case WYWOLAJ:
        system("./ApliBazaKs "+x.toAscii());
        break;
    case SQL:
        ile+=przyciski[id].wynik.count(';');
        typ_idw[0]=0;
        przyciski[id].wynik.split(';').at(zz);
        for(int i=0;i<il.pole_Tekst;i++)
        {
            ident=":"+pole_Tekst[i].ident;
            x.replace(ident,polaTekstowe[i]->text());
            if(przyciski[id].wynik.contains(';'));

            for(int j=0;j<ile;j++)if(pole_Tekst[i].ident==przyciski[id].wynik.split(';').at(j)){
                idw[zz]=i;nidw[zz]=j;
                typ_idw[zz++]=1;}
        }
        for(int i=0;i<il.pole;i++)
        {
            ident=":"+Pole[i].ident;
            x.replace(ident,Pole[i].tekst);
                    for(int j=0;j<ile;j++)if(Pole[i].ident==przyciski[id].wynik.split(';').at(j)){
                        idw[zz]=i;nidw[zz]=j;
                        typ_idw[zz++]=2;}
        }
        for(int i=0;i<il.tablica;i++)
        {
          for(int j=0;j<ile;j++)if(Tablica[i].ident==przyciski[id].wynik.split(';').at(j)){
                        idw[zz]=i;nidw[zz]=j;
                        typ_idw[zz++]=3;};
        }
        query=db.exec(x);
        for(int izz=0;izz<zz;izz++)
        {
        if(typ_idw[izz]==1){
            query.seek(0);
            //query.next();
            polaTekstowe[idw[izz]]->setText(query.value(nidw[izz]).toString());
        }
        if(typ_idw[izz]==2){
            query.seek(0);
            //query.next();
            Pole[idw[izz]].tekst=query.value(nidw[izz]).toString();
        }

        if(typ_idw[izz]==3){
            w=0;
            query.seek(0);
            tablice[idw[izz]]->setColumnCount(0);
            tablice[idw[izz]]->setRowCount(0);
           do
           {

                tablice[idw[izz]]->insertRow(w);
                k=0;
                while(query.value(k).isValid())
                              {
                   if(tablice[idw[izz]]->columnCount()<k+1)tablice[idw[izz]]->insertColumn(k);
                   if(w==0)kolumny.append(query.record().fieldName(k));
                   Items=new QTableWidgetItem(query.value(k).toString());
                   tablice[idw[izz]]->setItem(w, k++, Items);
                            }
                w++;
            } while(query.next());
            tablice[idw[izz]]->setHorizontalHeaderLabels(kolumny);
        }
        }
        break;
    case POLICZ:
        for(int i=0;i<il.pole_Tekst;i++)
        {
            x.replace(pole_Tekst[i].ident,polaTekstowe[i]->text());
            if(pole_Tekst[i].ident==przyciski[id].wynik)idw[0]=i;
        }
        for(int i=0;i<il.pole;i++)
        {
            x.replace(Pole[i].ident,Pole[i].tekst);
        }
        x.replace(",",".");
        x2 = myEngine.evaluate(x);
        polaTekstowe[idw[0]]->setText(x2.toString());
        break;
    }
}


MainWindow::MainWindow(QWidget *parent,QString p) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString t;
    LoginDialog log;
    il.Tekst=0;
    il.pole_Tekst=0;
    il.przyciski=0;
    il.tablica=0;
    plik=p;
    ui->setupUi(this);
    Odczytaj_XML(plik);
    Odczytaj_XMLBaza("baza.xml");
    if(baza.Typ!="QSQLITE" && baza.Typ!="QSQLITE2")
    {
    log.exec();
    baza.User=log.Login;
    baza.Password=log.Haslo;
    }
    createConnection(baza);
    //createBase();
 this->resize(szerokosc.toInt(),wysokosc.toInt());
    this->setWindowTitle(tytul);
    QTableWidget *tablica[il.tablica];
    if(il.tablica>0){
    for(int i=0;i<il.tablica;i++)
    {
        wiersz = Tablica[i].wiersz;
        pwiersz = Tablica[i].pwiersz;
        kolumna = Tablica[i].kolumna;
        pkolumna = Tablica[i].pkolumna;
        tablica[i] = new QTableWidget(this);
        tablica[i]->setObjectName(QString::fromUtf8("test"));
        tablica[i]->setGeometry(QRect(10, 100, 52, 13));
        tablica[i]->setColumnCount(Tablica[i].kolumny);
        tablica[i]->setRowCount(Tablica[i].wiersze);
            ui->gridLayout->addWidget(tablica[i],wiersz,kolumna,pwiersz,pkolumna);
            tablice[i]=tablica[i];
    }
     }
    if(il.Tekst>0){
    QLabel *tekst[il.Tekst];
    for(int i=0;i<il.Tekst;i++)
    {
        t=Tekst[i].tekst;
        wiersz = Tekst[i].wiersz;
        kolumna = Tekst[i].kolumna;
        pwiersz = Tekst[i].pwiersz;
        pkolumna = Tekst[i].pkolumna;
        tekst[i] = new QLabel(t,this);
        tekst[i]->setObjectName(QString::fromUtf8("test"));
        tekst[i]->setGeometry(QRect(10, 100, 52, 13));
        tekst[i]->setText(t);
        if(Tekst[i].tablica==99)
        {
            ui->gridLayout->addWidget(tekst[i],wiersz,kolumna,pwiersz,pkolumna);
        }else
        {
            tablica[Tekst[i].tablica]->setCellWidget(wiersz,kolumna,tekst[i]);
        }
    }
     }
    if(il.pole_Tekst>0){
     QLineEdit *pole_tekst[il.pole_Tekst];
   for(int i=0;i<il.pole_Tekst;i++)
   {
       t=pole_Tekst[i].tekst;
       wiersz = pole_Tekst[i].wiersz;
       kolumna = pole_Tekst[i].kolumna;
       pwiersz = pole_Tekst[i].pwiersz;
       pkolumna = pole_Tekst[i].pkolumna;
       pole_tekst[i] = new QLineEdit(t,this);
       pole_tekst[i]->setObjectName(QString::fromUtf8("test"));
       pole_tekst[i]->setText(t);
               if(pole_Tekst[i].tablica==99)
               {
                   ui->gridLayout->addWidget(pole_tekst[i],wiersz,kolumna,pwiersz,pkolumna);
               }else
               {
                   tablica[pole_Tekst[i].tablica]->setCellWidget(wiersz,kolumna,pole_tekst[i]);
               }
       polaTekstowe[i]=pole_tekst[i];
    }
    }

    if(il.przyciski>0){
     QPushButton *Przycisk[il.przyciski];
     signalMapper = new QSignalMapper(this);
     for(int i=0;i<il.przyciski;i++)
     {
         t=przyciski[i].tekst;
         wiersz = przyciski[i].wiersz;
         kolumna = przyciski[i].kolumna;
         pwiersz = przyciski[i].pwiersz;
         pkolumna = przyciski[i].pkolumna;
         Przycisk[i] = new QPushButton(ui->gridLayout->widget());
         Przycisk[i]->setObjectName(QString::fromUtf8("test"));
         Przycisk[i]->setText(t);

         if(przyciski[i].tablica==99)
         {
             ui->gridLayout->addWidget(Przycisk[i],wiersz,kolumna,pwiersz,pkolumna);
             signalMapper->setMapping(ui->gridLayout->itemAtPosition(wiersz,kolumna)->widget(),i);
         }else
         {
             tablica[przyciski[i].tablica]->setCellWidget(wiersz,kolumna,Przycisk[i]);

             signalMapper->setMapping(tablica[przyciski[i].tablica]->cellWidget(wiersz,kolumna),i);
           }
         MainWindow::QObject::connect(Przycisk[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
    }
     connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(on_przycisk_klik(int)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
