#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sharedtypes.h"
#include "xmlreader.h"

static QString wysokosc,szerokosc, tytul;
int wiersz, kolumna, pwiersz, pkolumna;
void MainWindow::Odczytaj_XML(const QString &fileName) {
    Elementy Element;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    XMLReader reader(&file,&objectCounter);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            Element=reader.readTypeOfElement();
            switch(Element)
            {
             case TYTUL:
                tytul = reader.readElementText();
             break;
             case OKNO:
                wysokosc=reader.getStringAttribute(tr("w"));
                szerokosc=reader.getStringAttribute(tr("s"));
             break;
             case TEKST:
                reader.readObiekt(&tekst[objectCounter.tekst]);
                ++objectCounter.tekst;
             break;
             case POLETEKST:
                reader.readObiekt(&poleTekst[objectCounter.poleTekst]);
                ++objectCounter.poleTekst;
             break;
            case TABLICA:
                reader.readTablica(&tablica[objectCounter.tablica]);
               ++objectCounter.tablica;
            break;
            case WR:
              akt_wiersz=true;
               ++tablica[objectCounter.tablica-1].wiersze;
            break;
            case POLE:
                reader.readObiekt(&pole[objectCounter.pole]);
               ++objectCounter.pole;
            break;
             case PRZYCISK:
                reader.readPrzycisk(&przyciski[objectCounter.przyciski]);
                ++objectCounter.przyciski;
             break;
               default:
                break;
            }
        }
        if (reader.isEndElement())
        {
         if(reader.isNameEqual(tr("tablica")))
         {
             akt_tablica=false;
         }
         if(reader.isNameEqual(tr("wr")))
         {
           akt_wiersz=false;
           if(tablica[objectCounter.tablica-1].kolumny<reader.elem)tablica[objectCounter.tablica-1].kolumny=reader.elem;
           reader.elem=0;
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

MainWindow::MainWindow(QWidget *parent,QString plik) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString textTmp;
    LoginDialog loginDialog;
    ui->setupUi(this);
    Odczytaj_XML(plik);
    Odczytaj_XMLBaza("baza.xml");
    if(baza.Typ!="QSQLITE" && baza.Typ!="QSQLITE2")
    {
        loginDialog.Login=baza.User;
    if(baza.Password=="")
    {
    loginDialog.exec();
    baza.User=loginDialog.Login;
    baza.Password=loginDialog.Haslo;
    }
    }
    createConnection(baza);
 this->resize(szerokosc.toInt(),wysokosc.toInt());
    this->setWindowTitle(tytul);
    tablice= new QTableWidget*[objectCounter.tablica];
    if(objectCounter.tablica>0){
    for(int i=0;i<objectCounter.tablica;i++)
    {
        wiersz = tablica[i].wiersz;
        pwiersz = tablica[i].pwiersz;
        kolumna = tablica[i].kolumna;
        pkolumna = tablica[i].pkolumna;
        tablice[i] = new QTableWidget(this);
        tablice[i]->setObjectName(QString::fromUtf8("test"));
        tablice[i]->setGeometry(QRect(10, 100, 52, 13));
        tablice[i]->setColumnCount(tablica[i].kolumny);
        tablice[i]->setRowCount(tablica[i].wiersze);
            ui->gridLayout->addWidget(tablice[i],wiersz,kolumna,pwiersz,pkolumna);
            akcjeTablica[i].id=i;
    connect(tablice[i],SIGNAL(cellDoubleClicked(int,int)),&akcjeTablica[i],SLOT(on_tablica_click(int,int)));
  }
     }
    if(objectCounter.tekst>0){
    pola= new QLabel*[objectCounter.tekst];
    for(int i=0;i<objectCounter.tekst;i++)
    {
        textTmp=tekst[i].tekst;
        wiersz = tekst[i].wiersz;
        kolumna = tekst[i].kolumna;
        pwiersz = tekst[i].pwiersz;
        pkolumna = tekst[i].pkolumna;
        pola[i] = new QLabel(textTmp,this);
        pola[i]->setObjectName(QString::fromUtf8("test"));
        pola[i]->setGeometry(QRect(10, 100, 52, 13));
        pola[i]->setText(textTmp);
        if(tekst[i].tablica==99)
        {
            ui->gridLayout->addWidget(pola[i],wiersz,kolumna,pwiersz,pkolumna);
        }else
        {
            tablice[tekst[i].tablica]->setCellWidget(wiersz,kolumna,pola[i]);
        }
    }
     }
    if(objectCounter.poleTekst>0){
     polaTekstowe= new QLineEdit*[objectCounter.poleTekst];
   for(int i=0;i<objectCounter.poleTekst;i++)
   {
       textTmp=poleTekst[i].tekst;
       wiersz = poleTekst[i].wiersz;
       kolumna = poleTekst[i].kolumna;
       pwiersz = poleTekst[i].pwiersz;
       pkolumna = poleTekst[i].pkolumna;
       polaTekstowe[i] = new QLineEdit(textTmp,this);
       polaTekstowe[i]->setObjectName(QString::fromUtf8("test"));
       polaTekstowe[i]->setText(textTmp);
               if(poleTekst[i].tablica==99)
               {
                   ui->gridLayout->addWidget(polaTekstowe[i],wiersz,kolumna,pwiersz,pkolumna);
               }else
               {
                   tablice[poleTekst[i].tablica]->setCellWidget(wiersz,kolumna,polaTekstowe[i]);
               }
    }
    }

    if(objectCounter.przyciski>0){
     QPushButton *Przycisk[objectCounter.przyciski];
     signalMapper = new QSignalMapper(this);
     for(int i=0;i<objectCounter.przyciski;i++)
     {
         textTmp=przyciski[i].tekst;
         wiersz = przyciski[i].wiersz;
         kolumna = przyciski[i].kolumna;
         pwiersz = przyciski[i].pwiersz;
         pkolumna = przyciski[i].pkolumna;
         Przycisk[i] = new QPushButton(ui->gridLayout->widget());
         Przycisk[i]->setObjectName(QString::fromUtf8("test"));
         Przycisk[i]->setText(textTmp);

         if(przyciski[i].tablica==99)
         {
             ui->gridLayout->addWidget(Przycisk[i],wiersz,kolumna,pwiersz,pkolumna);
             signalMapper->setMapping(ui->gridLayout->itemAtPosition(wiersz,kolumna)->widget(),i);
         }else
         {
             tablice[przyciski[i].tablica]->setCellWidget(wiersz,kolumna,Przycisk[i]);

             signalMapper->setMapping(tablice[przyciski[i].tablica]->cellWidget(wiersz,kolumna),i);
           }
         MainWindow::QObject::connect(Przycisk[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
    }
     akcjaPrzycisk.parentWindow=this;
     connect(signalMapper,SIGNAL(mapped(int)),&akcjaPrzycisk,SLOT(on_przycisk_click(int)));

    }
}

MainWindow::~MainWindow()
{
    for(int i=0;i<objectCounter.poleTekst;i++)
    {
     delete polaTekstowe[i];
    }
    for(int i=0;i<objectCounter.tablica;i++)
    {
     delete tablice[i];
    }
    for(int i=0;i<objectCounter.pole;i++)
    {
     delete pola[i];
    }
    delete ui;
}
