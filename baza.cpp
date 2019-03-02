#include "baza.h"

Baza::Baza()
{
    Port=0;
}
QSqlDatabase db;
QSqlQuery query("",db);
bool createConnection(Baza A)
{
   db = QSqlDatabase::addDatabase(A.Typ);
    if(!A.Nazwa.isEmpty())db.setDatabaseName(A.Nazwa);
    if(!A.User.isEmpty())db.setUserName(A.User);
    if(!A.Password.isEmpty())db.setPassword(A.Password);
    if(!A.Host.isEmpty())db.setHostName(A.Host);
    if(A.Port!=0)db.setPort(A.Port);
    if (!db.open()) {
        QMessageBox::critical(0, QString::fromUtf8("Nie można połączyć z bazą danych"),
                              QString::fromUtf8("Nie można ustanowić połączenia z bazą danych."), QMessageBox::Cancel);
        return false;
    }
    return true;
}
