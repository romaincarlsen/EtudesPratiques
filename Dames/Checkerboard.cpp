#include "Checkerboard.h"
#include "stdafx.h"

#include "Checkerboard.h"

// create checkerboard with dimension parameters
Checkerboard::Checkerboard(int nbLine, int nbColumn)
{
	// init dimension
	this->nbColumn = nbColumn ;
	this->nbLine = nbLine ;
	
	// init squares with EMPTY and LOCK type
	square = new SQUARE*[this->nbColumn] ;
	for (int x=0 ; x<this->nbColumn ; x++) {
		square[x] = new SQUARE[this->nbLine] ;
		for (int y=0 ; y<this->nbLine ; y++)
			if ((isEven(x) && isEven(y)) || (isOdd(x) && isOdd(y)))
				square[x][y] = EMPTY ;
			else
				square[x][y] = LOCK ;
	}
}


Checkerboard::~Checkerboard(void)
{
	for (int x=0 ; x<this->nbColumn ; x++)
		delete square[x] ;
	delete square ;
}

int Checkerboard::getNbColumn() {
	return nbColumn ;
}

int Checkerboard::getNbLine() {
	return nbLine ;
}

void Checkerboard::setSquare(int x, int y, SQUARE square) {
	this->square[x][y]= square ;
}

SQUARE** Checkerboard::getSquare() {
	return square ;
}
// put Piece on the Checkerboard
bool Checkerboard::putPiece(int x, int y, SQUARE piece) {
	//Test if the square is empty
	if (square[x][y] == EMPTY) {
		square[x][y] = piece ;
		return true;
	}
	return false ;
}

// print checkerboard
void Checkerboard::print(void)
{
	cout << endl ;
	for (int y=this->nbLine-1 ; y>=0 ; y--) {
		for (int x=0 ; x<this->nbColumn ; x++)
			cout << square_to_char(square[x][y]) ;
		cout << " " << y+1 << endl ;
	}
	cout << endl ;
	for (int x=0 ; x<this->nbColumn ; x++)
		cout << num_to_letter_column(x+1) ;
	cout << endl ;
}