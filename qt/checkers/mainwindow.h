#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"

#include "struct.h"
#include "Tools.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "labelcase.h"
#include <windef.h>
#include <windows.h>
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
    //attributs de stockage de la configuration du jeu (alphabéta, fonctions de coûts, parallélisation, reporting)
    bool with_alphabeta;
    bool with_thread;
    bool _reporting;
    int costFunctionP1;
    int costFunctionP2;
    //Tableau des Label contenant les images du jeu
    Board _square;
    //Taille du damier
    int size;

public slots:
    //Slot gérant l'appuie sur le bouton start
    void start_click() ;
    //slot gérant les clics sur le damier
    void click(int x, int y);
    void launchIA() ;
    //slots gérant la configuration du jeu
    void setAlphaBeta(bool a);
    void setThreads(bool t);
    void setCostFunction1(int f);
    void setCostFunction2(int f);
    void setReporting(bool report);
    //slot fermant le jeu
    void closeEvent(QCloseEvent * event );

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
    // print checkerboard
    void paint(bool firstPrint);

    //affiche la case sélectionnée
    void printSelect();


private:
    Ui::MainWindow *ui;
};
#else
class MainWindow ;
#endif // MAINWINDOW_H
