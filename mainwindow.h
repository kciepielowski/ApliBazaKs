#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QXmlStreamReader>
#include <QFile>
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, QString p = "okno.xml");
    ~MainWindow();
    QSignalMapper * signalMapper;
    QString plik;
private:
    Ui::MainWindow *ui;
private slots:
    void on_przycisk_klik(int);
};

enum funkcja{BRAK=0, ZAMKNIJ=1, POLICZ=2, WYWOLAJ=4, SQL=5};
struct ilObiektow
{
public:
    int8_t Tekst;
    int8_t pole_Tekst;
    int8_t przyciski;
    int8_t tablica;
    int8_t pole;
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

class Tablice: public Obiekt
{
public:
    int8_t wiersze;
    int8_t kolumny;
};

class Przycisk: public Obiekt
{
public:
    funkcja fn;
    QString parametr;
    QString wynik;
};
#endif // MAINWINDOW_H
