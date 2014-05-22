#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"

#include "struct.h"
#include "ui_mainwindow2.h"
#include "game.h"
#include "labelcase.h"
#include <sstream>



namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    Game* game ;
    QSQUARE square_clicked ;
    QTimer* iTimer ;
    //attributs stockant si le joueur est en manuel ou une IA et dans ce dernier cas son niveau
    int _p1;
    int _p2;
    //Attributs stockant la taille maximale de la fenêtre
    int width;
    int height;
    //attributs de stockage de la configuration du jeu (alphabéta, fonctions de coûts, parallélisation)
    bool with_alphabeta;
    bool with_thread;
    int costFunctionP1;
    int costFunctionP2;

public slots:
    void start_click() ;
    void click(int x, int y);
    void launchIA() ;
    void setAlphaBeta(bool a);
    void setThreads(bool t);
    void setCostFunction1(int f);
    void setCostFunction2(int f);

    //Méthode qui deselectionne le pion courant lorsque l'on fait un clic droit sauf si une prise est en cours
    bool deselect();

    //modifie le type de joueur (manuel ou IA) et le niveau dans le cas de l'IA
    void selectLevelPlayer1(int lvl);
    void selectLevelPlayer2(int lvl);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //Nettoye la grille du jeu
    void clear();

    int getheight();
    int getwidth();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
