#ifndef AKCJA_H
#define AKCJA_H

#include <QObject>
#include <QMainWindow>

class Akcja : public QObject
{
    Q_OBJECT

public:
    QMainWindow *parentWindow;
    int id;
private:
    QString paramText,param2Text, wynik;
    void zamknij();
    void wywolaj();
    void policz();
    void sql();
private slots:
    void on_tablica_click(int,int);
    void on_przycisk_click(int);
};

#endif // AKCJA_H
