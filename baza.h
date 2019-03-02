#ifndef BAZA_H
#define BAZA_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
class Baza
{
public:
    QString Typ;
    QString Nazwa;
    QString User;
    QString Password;
    QString Host;
    int Port;
    Baza();
};
extern QSqlDatabase db;
extern QSqlQuery query;
extern bool createConnection(Baza A);

#endif // BAZA_H
