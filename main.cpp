#include <QtGui/QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QString xml;
    xml=argv[1];
    if(xml=="")xml="okno.xml";
    MainWindow w(0,xml);
    w.show();
    
    return a.exec();
}
