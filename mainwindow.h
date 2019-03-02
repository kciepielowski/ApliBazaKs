#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
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
    void Odczytaj_XML(const QString&);

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
