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
            if (!((isEven(x) && isEven(y)) || (isOdd(x) && isOdd(y))))
                _square[x][y].square = LOCK ;
            else
                _square[x][y].square = EMPTY ;
            //_square[x][y].label = new QLabel();
            //gestion des labels contenant leur position :
            _square[x][y].label = new LabelCase(x,y);
        }
    }
}

Checkerboard::Checkerboard(Checkerboard* board) : _size(board->getSize())
{

    _square.resize(board->getSize(),vector<QSQUARE>(board->getSize()));
    // init squares with EMPTY and LOCK type

    //square = new SQUARE*[this->_size] ;
    for (int x=0 ; x<board->getSize() ; x++) {
        //_square[x] = new SQUARE[this->_size] ;
        for (int y=0 ; y<board->getSize() ; y++) {
            _square[x][y] = board->getSquare()[x][y] ;
        }
    }
}

Checkerboard::~Checkerboard(void)
{
    _square.~vector();
}

int Checkerboard::getSize() const{
    return _size ;
}

void Checkerboard::setSquare(int x, int y, SQUARE square) {
    this->_square[x][y].square= square ;
}

const Damier& Checkerboard::getSquare() const{
    return _square ;
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

//Permet de changer la case sélectionnée
void Checkerboard::select(int x, int y){
    selection.x = x;
    selection.y = y;
    selection.select = true;
}

//déselectionne la case
void Checkerboard::deselect(){
    selection.select = false;
}

// indicate if the checkerboard have a winner (if one player haven't pieces)
bool Checkerboard::isWin() const {
    int nbWhite = 0 ;
    int nbBlack = 0 ;
    for (int x=0 ; x<_size ; x++)
        for (int y=0 ; y<_size ; y++) {
            nbWhite += isWhite(_square[x][y].square) ;
            nbBlack += isBlack(_square[x][y].square) ;
        }
    return !nbWhite || !nbBlack ;
}

// print checkerboard
QString Checkerboard::toString(void)
{
    QString s = "\n" ;
    for (int y=this->_size-1 ; y>=0 ; y--) {
        for (int x=0 ; x<this->_size ; x++) {
            s +=  square_to_char(_square[x][y].square) ;

        }
        s += " " + QString::number(y+1) + "\n" ;
    }
    for (int x=0 ; x<this->_size ; x++)
        s += num_to_letter_column(x+1) ;
    s += "\n" ;
    return s ;
}

// print checkerboard
void Checkerboard::paint(QGridLayout* board_gl)
{
    for (int y=0 ; y<this->_size ; y++) {
        for (int x=0 ; x<this->_size ; x++) {
            _square[x][y].label->setPixmap(square_to_img(_square[x][y].square));
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


