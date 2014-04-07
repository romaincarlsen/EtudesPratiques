#include "mainwindow.h"
#include "LabelCase.h"

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

void MainWindow::ok_click(){
    game->clickOnBoard(this->ui->input) ;
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);
}

void MainWindow::click(int x, int y){
    game->clickOnBoard(x,y);
    this->ui->board_l->setText(game->toString()) ;
    game->paint(this->ui->board_gl);
}

void MainWindow::start_click(){
    int size = this->ui->size_tb->text().toInt() ;
    int nbLineP1 = this->ui->nbLineP1_tb->text().toInt() ;
    int nbLineP2 = this->ui->nbLineP2_tb->text().toInt() ;
    game = new Game(size, nbLineP1, nbLineP2) ;
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
