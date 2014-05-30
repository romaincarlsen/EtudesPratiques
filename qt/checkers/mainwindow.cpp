#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initialisation des attributs
    with_alphabeta = false;
    with_thread = false;
    _reporting = false;
    costFunctionP1 = 1;
    costFunctionP2 = 1;

    ui->setupUi(this);

    ui->size_tb->setText("10") ;
    ui->nbLineP1_tb->setText("4") ;
    ui->nbLineP2_tb->setText("4") ;

    //limitaion de la taille de la fenetre à la taille de l'écran
    QDesktopWidget *desktop = new QDesktopWidget;
    width = desktop->screenGeometry().width();
    height = desktop->screenGeometry().height();
    this->ui->centralwidget->setMaximumSize(width,height);

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

    //Connection des checkboxs et des attributs activant ou désactivant l'alpha-béta, les threads et le reporting
    ui->alphabeta->connect(ui->alphabeta,SIGNAL(clicked(bool)),this,SLOT(setAlphaBeta(bool)));
    ui->threads->connect(ui->threads,SIGNAL(clicked(bool)),this,SLOT(setThreads(bool)));
    ui->reporting->connect(ui->reporting,SIGNAL(clicked(bool)),this,SLOT(setReporting(bool)));

    //Initialisation des valeurs des spinbox pour le choix des fonctions de coût
    ui->fctcout1->setMinimum(1);
    ui->fctcout1->setMaximum(5);
    ui->fctcout2->setMinimum(1);
    ui->fctcout2->setMaximum(5);

    //Connection des spinbox déterminants les fonctions de coûts
    ui->fctcout1->connect(ui->fctcout1,SIGNAL(valueChanged(int)),this,SLOT(setCostFunction1(int)));
    ui->fctcout2->connect(ui->fctcout2,SIGNAL(valueChanged(int)),this,SLOT(setCostFunction2(int)));

    iTimer = new QTimer(this);

    this->connect(this->ui->start, SIGNAL(clicked()), this, SLOT(start_click()));
    this->connect(iTimer, SIGNAL(timeout()), this, SLOT(launchIA()));
    this->showMaximized();

    //Connection du slot de fermture de la fenetre (pour interrompre l'IA si le calcul est en cours
    this->connect(this,SIGNAL(destroyed()),this,SLOT(close()));
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
        this->ui->board_l->setText("Calcul du coup en cours");
        if (!game->isFinish()) {

            MOVE mv ;
            if (game->with_alphabeta)
                mv = game->alphaBeta(game->with_thread) ;
            else
                mv = game->negaMax(game->with_thread) ;

            if (game->execMove(mv.x,mv.y,-1,-1)) {
                this->ui->board_l->setText(game->toString()) ;
                paint(false);
            }
            if (game->execMove(-1,-1,mv.xDest,mv.yDest)) {
                this->ui->board_l->setText(game->toString()) ;
                paint(false);
            }
        }
        else {
            iTimer->stop();
        }
    }
}

void MainWindow::click(int x, int y){
    if (!game->isFinish()) {
        if (!game->isCPTurn()) {
            if (game->execMove(x,y,-1,-1)) {
                this->ui->board_l->setText(game->toString()) ;
                if(!game->isStateSelect()) ui->border->setCursor(Qt::ClosedHandCursor);
                else ui->border->setCursor(Qt::OpenHandCursor);
                paint(false);
            }
            if (game->execMove(-1,-1,x,y)) {
                if(!game->isStateSelect()) ui->border->setCursor(Qt::ClosedHandCursor);
                else ui->border->setCursor(Qt::OpenHandCursor);
                this->ui->board_l->setText(game->toString()) ;
                paint(false);
            }
        }
    }
    else
        iTimer->stop();
}

void MainWindow::start_click(){
    this->clear();
    size = this->ui->size_tb->text().toInt() ;
    int nbLineP1 = this->ui->nbLineP1_tb->text().toInt() ;
    int nbLineP2 = this->ui->nbLineP2_tb->text().toInt() ;

    //Mise en place d'une taille maximale au plateau
    this->ui->border->setMaximumSize(width-300,height-50);

    //Récupération de la taille de la barre des tâches
    HWND tTrayHwnd = FindWindow(L"Shell_TrayWnd", NULL);
    RECT tTrayRect;

    GetWindowRect(tTrayHwnd, &tTrayRect);
    int bar = this->height - ui->centralwidget->height();;

    //Calcul de la place disponible pour le damier
    int freeHeight = height - (tTrayRect.bottom - tTrayRect.top) - bar;
    int freeWidth = width - (tTrayRect.left - tTrayRect.right) -300;
    //Mise en place de la taille des cases du damier toute la place

    int min = std::min(freeWidth, freeHeight);

    int labelSize = min/size;
    //gestion des labels contenant leur position :

    //redimensionnement du tableau des labels
    _square.resize(size,vector<LabelCase*>(size));

    game = new Game(size, nbLineP1, nbLineP2,_p1, costFunctionP1,_p2, costFunctionP2, with_alphabeta, with_thread, _reporting) ;

    for (int i = 0; i< game->getSize(); i++){
        for (int j = 0; j< game->getSize(); j++){
            //creation des labels
            LabelCase* label = new LabelCase(i,j);
            _square[i][j] = label;
            label->setMinimumSize(0,0);
            label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            label->setScaledContents(true);

            //LabelCase* label = game->getBoard()->getQSquare(i,j).label;
            label->connect(label, SIGNAL(clicked(int,int)), this, SLOT(click(int, int)));
            label->connect(label, SIGNAL(deselect()), this, SLOT(deselect()));
            label->setMaximumSize(labelSize,labelSize);
        }
    }

    this->ui->board_l->setText(game->toString()) ;
    paint(true);
    this->ui->border->setFrameShape(QFrame::Box);
    iTimer->setInterval(1000);
    iTimer->start();

    //Changement du curseur pour une main sur le plateau
    ui->border->setCursor(Qt::OpenHandCursor);
}

//Méthode qui deselectionne le pion courant lorsque l'on fait un clic droit sauf si une prise est en cours
bool MainWindow::deselect(){
    if (game->deselect()) {
        paint(false);
        ui->border->setCursor(Qt::OpenHandCursor);
        return true ;
    }
    return false ;
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
    with_alphabeta = a;
}

void MainWindow::setThreads(bool t){
    with_thread = t;
    if (with_thread){
        this->ui->reporting->setChecked(false);
        _reporting = false;
    }
}

void MainWindow::setCostFunction1(int f){
    costFunctionP1 = f;
}

void MainWindow::setCostFunction2(int f){
    costFunctionP2 = f;
}

void MainWindow::setReporting(bool report){
    _reporting = report;
    if (_reporting){
        this->ui->threads->setChecked(false);
        with_thread = false;
    }
}


int MainWindow::getheight(){
    return height;
}

int MainWindow::getwidth(){
    return width;
}

int main(int argc, char *argv[])
{
    srand (time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show() ;
    return a.exec() ;
}
// print checkerboard
void MainWindow::paint(bool firstPrint)
{

    //tableau de jeu
    Checkerboard board(game->getBoard()) ;
    Damier square = board.getQSquare();
    for (int y=0 ; y<this->size ; y++) {
        for (int x=0 ; x<this->size ; x++) {
            _square[x][y]->setPixmap(Tools::square_to_img(square[x][y].square));
            _square[x][y]->setScaledContents(true);
            if(firstPrint) this->ui->board_gl->addWidget(_square[x][y], -(y-(this->size-1)), x) ;
        }
    }
    if(board.selection.select) printSelect();
}

//affiche la case sélectionnée
void MainWindow::printSelect(){
/*
    Checkerboard board(game->getBoard()) ;
    int x = board.selection.x;
    int y = board.selection.y;
    Damier squareTab = board.getQSquare();
    SQUARE square = squareTab[x][y].square ;
    QPixmap img;

    switch (square) {
    case BLACK_KING :	img = QPixmap("../checkers/img/black_king_select.png") ;
        break;
    case BLACK_PIECE :	img = QPixmap("../checkers/img/black_piece_select.png") ;
        break;
    case EMPTY :		img = QPixmap("../checkers/img/empty.png") ;
        break;
    case WHITE_PIECE :	img = QPixmap("../checkers/img/white_piece_select.png") ;
        break;
    case WHITE_KING :	img = QPixmap("../checkers/img/white_king_select.png") ;
        break;
    case LOCK :			img = QPixmap("../checkers/img/lock.png") ;
        break;
    default :			img = QPixmap() ;
    }
    _square[x][y]->setPixmap(img);
    _square[x][y]->setScaledContents(true);
*/
}
//Gestion de la fermeture de la fenetre

void MainWindow::closeEvent(QCloseEvent * event ){
    if (game != NULL)
        game->stop();
    event->accept();
}
