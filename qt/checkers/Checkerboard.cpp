#include "Checkerboard.h"


// create checkerboard with dimension parameters

Checkerboard::Checkerboard(int size) : _size(size)
{
    //initialisation de la sétection
    selection.select = false;
    _square.resize(size,vector<QSQUARE>(size));
    // init squares with EMPTY and LOCK type

    //square = new SQUARE*[this->_size] ;
    for (int x=0 ; x<size ; x++) {
        //_square[x] = new SQUARE[this->_size] ;
        for (int y=0 ; y<size ; y++) {
            _square[x][y].x = x ;
            _square[x][y].y = y ;
            if (!(Tools::isEven(x) && Tools::isEven(y) || Tools::isOdd(x) && Tools::isOdd(y)))
                _square[x][y].square = LOCK ;
            else
                _square[x][y].square = EMPTY ;
            //_square[x][y].label = new QLabel();
            //gestion des labels contenant leur position :
            _square[x][y].label = new LabelCase(x,y);
            _square[x][y].label->setMinimumSize(0,0);

            //int labelSize = 60 ; -> la taille est maintenant gérée directment dans mainwindow
            //_square[x][y].label->setMaximumSize(labelSize,labelSize);
            _square[x][y].label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            _square[x][y].label->setScaledContents(true);
        }
    }
}

Checkerboard::Checkerboard(Checkerboard* board) : _size(board->getSize())
{

    Damier test(board->getQSquare()) ;
    _square = test ;
}

Checkerboard::~Checkerboard(void)
{
    _square.~vector();
    std::cout <<"Board destroyed\n";
}

int Checkerboard::getSize() const{
    return _size ;
}

void Checkerboard::setSquare(int x, int y, SQUARE square) {
    this->_square[x][y].square= square ;
}

Damier Checkerboard::getQSquare() const {
    return _square ;
}

QSQUARE Checkerboard::getQSquare(int x, int y) const {
    if (x<_size && x>=0 && y<_size && y>=0){
        return _square[x][y] ;
    }
    else {
        qDebug()<<"Out of Board"<<endl;
    }
    QSQUARE error ;
    error.square = UNDEFINED ;
    error.x = -1 ;
    error.y = -1 ;
    error.label = NULL ;
    return error ;
}

SQUARE Checkerboard::getSquare(int x, int y) const{
    if (x<_size && x>=0 && y<_size && y>=0){
        return _square[x][y].square ;
    }
    else {
        qDebug()<<"Out of Board"<<endl;
    }
    return UNDEFINED ;
}

// put Piece on the Checkerboard
bool Checkerboard::putPiece(int x, int y, SQUARE piece) {
    //Test if the square is empty
    if (_square[x][y].square == EMPTY) {
        _square[x][y].square = piece ;
        return true;
    }
    return false ;
}

// delete pieces which have been killed during last turn
void Checkerboard::ghostBuster(void)
{
    for (int x=0 ; x<this->_size ; x++)
        for (int y=0 ; y<this->_size ; y++)
            _square[x][y].square = _square[x][y].square==GHOST ? EMPTY : _square[x][y].square ;
}

bool Checkerboard::moveBegined() {
    for (int x=0 ; x<this->_size ; x++)
        for (int y=0 ; y<this->_size ; y++)
            if (_square[x][y].square == GHOST)
                return true ;
    return false ;
}

//Permet de changer la case sélectionnée
void Checkerboard::select(int x, int y){
    selection.x = x;
    selection.y = y;
    selection.select = true;
}

//déselectionne la case
bool Checkerboard::deselect(){
    bool enCours = false;
    for(int i = 0; i<_size; i++){
        for(int j = 0; j<_size; j++){
            if(getQSquare(i,j).square == GHOST) {
                enCours = true;
            }
        }
    }
    if(!enCours){
        selection.select = false;
    }
    return !selection.select ;
}

// indicate if the checkerboard have a winner (if one player haven't pieces)
bool Checkerboard::isWin() const {
    int nbWhite = 0 ;
    int nbBlack = 0 ;
    for (int x=0 ; x<_size ; x++)
        for (int y=0 ; y<_size ; y++) {
            nbWhite += Tools::isWhite(_square[x][y].square) ;
            nbBlack += Tools::isBlack(_square[x][y].square) ;
        }
    return !nbWhite || !nbBlack ;
}

// scan the checkerboard in a file

string Checkerboard::toString()
{   string res ="";
    for (int y=0 ; y<this->_size ; y++) {
        for (int x=0 ; x<this->_size ; x++) {
            res += Tools::square_to_char(_square[x][y].square);
        }
    }
    return res;
}

// print checkerboard
void Checkerboard::paint(QGridLayout* board_gl)
{
    for (int y=0 ; y<this->_size ; y++) {
        for (int x=0 ; x<this->_size ; x++) {
            _square[x][y].label->setPixmap(Tools::square_to_img(_square[x][y].square));
            _square[x][y].label->setScaledContents(true);
            board_gl->addWidget(_square[x][y].label, -(y-(this->_size-1)), x) ;
        }
    }
    if (selection.select) printSelect(board_gl);
}

//affiche la case sélectionnée
void Checkerboard::printSelect(QGridLayout* board_gl){

    int x = selection.x;
    int y = selection.y;
    SQUARE square(_square[x][y].square);
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
    _square[x][y].label->setPixmap(img);
    _square[x][y].label->setScaledContents(true);
    board_gl->addWidget(_square[x][y].label, -(y-(this->_size-1)), x) ;
}


