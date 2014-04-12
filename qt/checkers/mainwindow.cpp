#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->size_tb->setText("10") ;
    ui->nbLineP1_tb->setText("4") ;
    ui->nbLineP2_tb->setText("4") ;

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
            MOVE mv = game->negaMax() ;

            qDebug() << mv.x << " " << mv.y << " " << mv.xDest << " " << mv.yDest << endl ;

            if (game->execMove(mv.x,mv.y,-1,-1)) {
                this->ui->board_l->setText(game->toString()) ;
                game->paint(this->ui->board_gl);
            }
            /*else {*/
                if (game->execMove(-1,-1,mv.xDest,mv.yDest)) {
                    this->ui->board_l->setText(game->toString()) ;
                    game->paint(this->ui->board_gl);
                }
            /*}*/
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
    game = new Game(size, nbLineP1, nbLineP2) ;
    for (int i = 0; i< game->getBoard()->getSize(); i++){
        for (int j = 0; j< game->getBoard()->getSize(); j++){
            LabelCase* label = game->getBoard()->getQSquare(i,j).label;
            label->connect(label, SIGNAL(clicked(int,int)), this, SLOT(click(int, int)));
        }
    }
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);

    iTimer->setInterval(1000);
    iTimer->start();

    //launchIA() ;
}

int main(int argc, char *argv[])
{
    srand (time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show() ;
    return a.exec() ;
}
