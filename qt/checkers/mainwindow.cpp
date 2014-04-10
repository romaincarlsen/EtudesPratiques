#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->size_tb->setText("10") ;
    ui->nbLineP1_tb->setText("4") ;
    ui->nbLineP2_tb->setText("4") ;

    this->connect(this->ui->ok, SIGNAL(clicked()), this, SLOT(ok_click()));
    this->connect(this->ui->start, SIGNAL(clicked()), this, SLOT(start_click()));
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

void MainWindow::ok_click(){
    game->clickOnBoard(this->ui->input) ;
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);
}

void MainWindow::click(int x, int y){
    game->clickOnBoard(x+1,y+1);
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);
    //qDebug() << "clic pris en compte en x : " << x+1 << ", y : " << y+1 << endl;
}

void MainWindow::start_click(){
    this->clear();
    int size = this->ui->size_tb->text().toInt() ;
    int nbLineP1 = this->ui->nbLineP1_tb->text().toInt() ;
    int nbLineP2 = this->ui->nbLineP2_tb->text().toInt() ;
    game = new Game(size, nbLineP1, nbLineP2) ;
    for (int i = 0; i< game->getBoard()->getSize(); i++){
        for (int j = 0; j< game->getBoard()->getSize(); j++){
            LabelCase* label = (game->getBoard()->getSquare())[i][j].label;
            label->connect(label, SIGNAL(clicked(int,int)), this, SLOT(click(int, int)));
        }
    }
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);

}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show() ;
    return a.exec() ;
}
