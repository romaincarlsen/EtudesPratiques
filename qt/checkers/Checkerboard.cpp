#include "Checkerboard.h"

// create checkerboard with dimension parameters

Checkerboard::Checkerboard(int size) : _size(size)
{

	_square.resize(size,vector<SQUARE>(size,EMPTY));
	// init squares with EMPTY and LOCK type
	
	//square = new SQUARE*[this->_size] ;
	for (int x=0 ; x<size ; x++) {
		//_square[x] = new SQUARE[this->_size] ;
		for (int y=0 ; y<size ; y++) {
			if (!((isEven(x) && isEven(y)) || (isOdd(x) && isOdd(y))))
				_square[x][y] = LOCK ;
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
	this->_square[x][y]= square ;
}

const Damier& Checkerboard::getSquare() const{
	return _square ;
}
// put Piece on the Checkerboard
bool Checkerboard::putPiece(int x, int y, SQUARE piece) {
	//Test if the square is empty
	if (_square[x][y] == EMPTY) {
		_square[x][y] = piece ;
		return true;
	}
	return false ;
}

// delete pieces which have been killed during last turn
void Checkerboard::ghostBuster(void)
{
	for (int x=0 ; x<this->_size ; x++)
		for (int y=0 ; y<this->_size ; y++)
			_square[x][y] = _square[x][y]==GHOST ? EMPTY : _square[x][y] ;
}

// indicate if the checkerboard have a winner (if one player haven't pieces)
bool Checkerboard::isWin() const {
	int nbWhite = 0 ;
	int nbBlack = 0 ;
	for (int x=0 ; x<_size ; x++)
		for (int y=0 ; y<_size ; y++) {
			nbWhite += isWhite(_square[x][y]) ;
			nbBlack += isBlack(_square[x][y]) ;
		}
	return !nbWhite || !nbBlack ;
}

// print checkerboard
void Checkerboard::print(void)
{
    qDebug() << endl ;
    QString line = "" ;
	for (int y=this->_size-1 ; y>=0 ; y--) {
		for (int x=0 ; x<this->_size ; x++)
            line += square_to_char(_square[x][y]) ;
        qDebug() << line << " " << y+1 ;
        line = "" ;
	}
	for (int x=0 ; x<this->_size ; x++)
        line += num_to_letter_column(x+1) ;
    qDebug() << endl << line << endl ;
}
