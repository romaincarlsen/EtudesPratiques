#include "stdafx.h"
#include <iostream>
#include "main.h"
#include "Checkerboard.h"

using namespace std ;

// create checkerboard with dimension parameters
Checkerboard::Checkerboard(int nbLine, int nbColumn)
{
	// init dimension
	this->nbColumn = nbColumn ;
	this->nbLine = nbLine ;
	
	// init squares with EMPTY type
	square = new int*[this->nbColumn] ;
	for (int x=0 ; x<this->nbColumn ; x++) {
		square[x] = new int[this->nbLine] ;
		for (int y=0 ; y<this->nbLine ; y++)
			square[x][y] = EMPTY ;
	}
}


Checkerboard::~Checkerboard(void)
{
	for (int x=0 ; x<this->nbColumn ; x++)
		delete square[x] ;
	delete square ;
}

// print checkerboard
void Checkerboard::print(void)
{
	for (int y=0 ; y<this->nbLine ; y++) {
		for (int x=0 ; x<this->nbColumn ; x++)
			cout << square[x][y] ;
		cout << endl ;
	}
}