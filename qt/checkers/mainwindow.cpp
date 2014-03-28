#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connect(this->ui->ok, SIGNAL(clicked()), this, SLOT(ok_click()));
    this->connect(this->ui->start, SIGNAL(clicked()), this, SLOT(start_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ok_click(){
    game.read(this->ui->input) ;
}

void MainWindow::start_click(){
    this->game.start() ;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show() ;
    return a.exec() ;
}
