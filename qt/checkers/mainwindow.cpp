#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->size_tb->setText("10") ;
    ui->nbLineP1_tb->setText("4") ;
    ui->nbLineP2_tb->setText("4") ;
    //adaptation à la taille de l'écran (test)
    QDesktopWidget *desktop = new QDesktopWidget;
    int largeur = desktop->screenGeometry().width();
    int hauteur = desktop->screenGeometry().height();
    this->ui->centralwidget->setMaximumSize(largeur,hauteur);

    //valeur par défaut pour le mode de jeu : manuel
    _p1 = -1;
    _p2 = -1;

    //mise en place des listes pour le choix du mode de jeu: manuel ou IA et niveau de l'IA
    ui->modeP1_IA->addItem("manual");
    ui->modeP2_IA->addItem("manual");

    for(int i = 1; i<11;i++){
        QString s = "IA level : ";
        QString nb(QString::number(i));
        //joueur 1
        ui->modeP1_IA->addItem(s+nb);
        ui->modeP1_IA->connect(ui->modeP1_IA,SIGNAL(currentIndexChanged(int)),this,SLOT(selectLevelPlayer1(int)));

        //joueur 2
        ui->modeP2_IA->addItem(s+nb);
        ui->modeP2_IA->connect(ui->modeP2_IA,SIGNAL(currentIndexChanged(int)),this,SLOT(selectLevelPlayer2(int)));
    }

    //Connection des checkboxs et des attributs activant ou désactivant l'alpha-béta et les threads
    ui->alphabeta->connect(ui->alphabeta,SIGNAL(clicked(bool)),this,SLOT(setAlphaBeta(bool)));
    ui->threads->connect(ui->threads,SIGNAL(clicked(bool)),this,SLOT(setThreads(bool)));

    iTimer = new QTimer(this);

    this->connect(this->ui->start, SIGNAL(clicked()), this, SLOT(start_click()));
    this->connect(iTimer, SIGNAL(timeout()), this, SLOT(launchIA()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Nettoye la grille du jeu
void MainWindow::clear(){
    QLayoutItem *child;
    while ((child = this->ui->board_gl->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
}

void MainWindow::launchIA() {
    if (game->isCPTurn()) {
        if (!game->isFinish()) {

            MOVE mv ;
            if (game->with_alphabeta)
                mv = game->alphaBeta(game->with_thread) ;
            else
                mv = game->negaMax(game->with_thread) ;

            if (game->execMove(mv.x,mv.y,-1,-1)) {
                this->ui->board_l->setText(game->toString()) ;
                game->paint(this->ui->board_gl);
            }
            if (game->execMove(-1,-1,mv.xDest,mv.yDest)) {
                this->ui->board_l->setText(game->toString()) ;
                game->paint(this->ui->board_gl);
            }
        }
        else {
            iTimer->stop();
        }
    }
}

void MainWindow::click(int x, int y){
    //launchIA() ;
    if (!game->isFinish()) {
        if (!game->isCPTurn()) {
            if (game->execMove(x,y,-1,-1)) {
                this->ui->board_l->setText(game->toString()) ;
                game->paint(this->ui->board_gl);
            }
            if (game->execMove(-1,-1,x,y)) {
                this->ui->board_l->setText(game->toString()) ;
                game->paint(this->ui->board_gl);
            }
        }
    }
    else
        iTimer->stop();
    //launchIA() ;
}

void MainWindow::start_click(){
    this->clear();
    int size = this->ui->size_tb->text().toInt() ;
    int nbLineP1 = this->ui->nbLineP1_tb->text().toInt() ;
    int nbLineP2 = this->ui->nbLineP2_tb->text().toInt() ;
    game = new Game(size, nbLineP1, nbLineP2,_p1,_p2) ;
    for (int i = 0; i< game->getBoard()->getSize(); i++){
        for (int j = 0; j< game->getBoard()->getSize(); j++){
            LabelCase* label = game->getBoard()->getQSquare(i,j).label;
            label->connect(label, SIGNAL(clicked(int,int)), this, SLOT(click(int, int)));
            label->connect(label, SIGNAL(deselect()), this, SLOT(deselect()));
        }
    }
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);
    this->ui->border->setFrameShape(QFrame::Box);
    iTimer->setInterval(1000);
    iTimer->start();

    //launchIA() ;
}

//Méthode qui deselectionne le pion courant lorsque l'on fait un clic droit sauf si une prise est en cours
void MainWindow::deselect(){
    Checkerboard* board = game->getBoard();
    int size = game->getSize();
    bool enCours = false;
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(board->getQSquare(i,j).square == GHOST) {enCours = true;}
        }
    }
    if(!enCours){
        game->deselect();
        game->paint(this->ui->board_gl);
    }
}

//modifie le type de joueur (manuel ou IA) et le niveau dans le cas de l'IA
void MainWindow::selectLevelPlayer1(int lvl){
    if (lvl == 0) _p1 = -1;
    else _p1 = lvl;

}

void MainWindow::selectLevelPlayer2(int lvl){
    if (lvl == 0) _p2 = -1;
    else _p2 = lvl;
}

void MainWindow::setAlphaBeta(bool a){
    game->with_alphabeta = a;
}

void MainWindow::setThreads(bool t){
    game->with_thread = t;
}

int main(int argc, char *argv[])
{
    srand (time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show() ;
    return a.exec() ;
}
