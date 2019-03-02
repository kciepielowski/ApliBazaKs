#include <QtGui/QApplication>
#include "mainwindow.h"
#include "sharedtypes.h"
#include "QTextCodec"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));
    QApplication a(argc, argv);
    programName=argv[0];
    QString xml;
    xml=argv[1];
    if(argc>1)baza.User=argv[2];
    if(argc>2)baza.Password=argv[3];
    if(xml=="")xml="okno.xml";
    MainWindow w(0,xml);
    w.show();
    return a.exec();
}
