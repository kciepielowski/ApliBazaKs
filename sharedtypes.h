#ifndef SHAREDTYPES
#define SHAREDTYPES
#include "QStringList"
#include "baza.h"
#include "akcja.h"
#include "objects.h"
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtScript/QScriptEngine>
#include <QObject>

extern bool akt_wiersz, akt_tablica;
extern QString programName;
extern QTableWidgetItem *itemPointer;
extern QLineEdit **polaTekstowe;
extern QLabel **pola;
extern QTableWidget **tablice;
extern Baza baza;
extern Akcja akcjeTablica[], akcjaPrzycisk;
extern IloscObiektow objectCounter;
extern Obiekt tekst[], poleTekst[], pole[];
extern Przycisk przyciski[];
extern Tablice tablica[];

#endif // SHAREDTYPES

