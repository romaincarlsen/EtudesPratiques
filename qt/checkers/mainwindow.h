#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"

#include "struct.h"
#include "ui_mainwindow.h"

extern QString in ;
extern void (*next)() ;
extern void start() ;

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void ok_click() ;
    void start_click() ;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
