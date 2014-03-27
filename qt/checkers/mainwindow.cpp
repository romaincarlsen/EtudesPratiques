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
    in = this->ui->input->text();
    this->ui->input->clear();
    if (next!=NULL)
        next() ;
}

void MainWindow::start_click(){
    start() ;
}
