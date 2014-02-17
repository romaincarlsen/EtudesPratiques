#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include "tools.h"

class Checkerboard
{

private:
	int nbColumn ;
	int nbLine ;
	SQUARE** square ;
public:
	// create checkerboard with dimension parameters
	Checkerboard(int nbLine, int nbColumn);
	~Checkerboard(void);

	int getNbColumn() ;

	int getNbLine();

	void setSquare(int x, int y, SQUARE square);

	SQUARE** getSquare() ;
	// put Piece on the Checkerboard
	bool putPiece(int x, int y, SQUARE piece) ;

	// print checkerboard
	void print() ;
};

#endif