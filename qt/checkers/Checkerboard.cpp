#include "Checkerboard.h"

// create checkerboard with dimension parameters
Checkerboard::Checkerboard() {

}

Checkerboard::Checkerboard(int size) : _size(size)
{
    //initialisation de la sétection
    selection.select = false;
    _square.resize(size,vector<QSQUARE>(size));
    // init squares with EMPTY and LOCK type
    for (int x=0 ; x<size ; x++) {
        for (int y=0 ; y<size ; y++) {
            _square[x][y].x = x ;
            _square[x][y].y = y ;
            if (!((Tools::isEven(x) && Tools::isEven(y)) || (Tools::isOdd(x) && Tools::isOdd(y))))
                _square[x][y].square = LOCK ;
            else
                _square[x][y].square = EMPTY ;
        }
    }
}

Checkerboard::Checkerboard(const Checkerboard & board) : _size(board.getSize()),_square(board.getQSquare())
{
}

Checkerboard::~Checkerboard(void)
{
}

int Checkerboard::getSize() const{
    return _size ;
}

void Checkerboard::setSquare(int x, int y, SQUARE square) {
    this->_square[x][y].square = square ;
}

Damier Checkerboard::getQSquare() const {
    return _square ;
}

QSQUARE Checkerboard::getQSquare(int x, int y) const {
    // verify if the x y indicate are in the board
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
    return error ;
}

SQUARE Checkerboard::getSquare(int x, int y) const{
    // verify if the x y indicate are in the board
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
    // research and return true if there is a GHOST square on the board
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

    // s'il n'y a pas de mouvement en cours, la piece est bien désélectionnée
    if(!isCurrentKill()) {
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

bool Checkerboard::isCurrentKill() const {
    // verify qu'il n'y ai pas de movemeent en cours
    for(int i = 0; i<_size; i++){
        for(int j = 0; j<_size; j++){
            if(getQSquare(i,j).square == GHOST) {
                return true ;
            }
        }
    }
    return false ;
}

string Checkerboard::toString() const
{   string res ="";
    for (int y=0 ; y<this->_size ; y++) {
        for (int x=0 ; x<this->_size ; x++) {
            res += Tools::square_to_char(_square[x][y].square);
            //res += static_cast<ostringstream*>( &(ostringstream() << (int)_square[x][y].square) )->str() ;
        }
    }
    return res;
}
