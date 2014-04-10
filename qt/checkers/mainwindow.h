#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"

#include "struct.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "labelcase.h"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    Game* game ;
    QSQUARE square_clicked ;

public slots:
    void ok_click() ;
    void start_click() ;
    void click(int x, int y);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //Nettoye la grille du jeu
    void MainWindow::clear();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
