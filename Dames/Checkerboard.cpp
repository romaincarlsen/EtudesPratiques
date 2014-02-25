//#include "Checkerboard.h"
#include "stdafx.h"

// create checkerboard with dimension parameters

Checkerboard::Checkerboard(int nbLine, int nbColumn) : _nbColumn(nbColumn), _nbLine(nbLine)
{
	// init dimension
	//this->_nbColumn = nbColumn ;
	//this->_nbLine = nbLine ;
	
	_square.resize(nbLine,vector<SQUARE>(nbColumn,EMPTY));
	// init squares with EMPTY and LOCK type
	
	//square = new SQUARE*[this->nbColumn] ;
	for (int x=0 ; x<this->_nbColumn ; x++) {
		//_square[x] = new SQUARE[this->_nbLine] ;
		for (int y=0 ; y<this->_nbLine ; y++)
			if ((isEven(x) && isEven(y)) || (isOdd(x) && isOdd(y)))
				_square[x][y] = EMPTY ;
			else
				_square[x][y] = LOCK ;
	}
	
}


Checkerboard::~Checkerboard(void)
{
	 _square.~vector();
}

int Checkerboard::getNbColumn() const{
	return _nbColumn ;
}

int Checkerboard::getNbLine() const {
	return _nbLine ;
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

// print checkerboard
void Checkerboard::print(void)
{
	cout << endl ;
	for (int y=this->_nbLine-1 ; y>=0 ; y--) {
		for (int x=0 ; x<this->_nbColumn ; x++)
			cout << square_to_char(_square[x][y]) ;
		cout << " " << y+1 << endl ;
	}
	cout << endl ;
	for (int x=0 ; x<this->_nbColumn ; x++)
		cout << num_to_letter_column(x+1) ;
	cout << endl ;
}