#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include "tools.h"

typedef std::vector<std::vector<SQUARE>> Damier;

class Checkerboard
{

private:
	int _nbColumn ;
	int _nbLine ;
	//SQUARE** square ;
	Damier _square;
public:
	// create checkerboard with dimension parameters
	Checkerboard(int nbLine, int nbColumn);
	~Checkerboard(void);

	int getNbColumn() const;

	int getNbLine() const;

	void setSquare(int x, int y, SQUARE square);

	//SQUARE** getSquare() ;
	const Damier& getSquare() const;
	// put Piece on the Checkerboard
	bool putPiece(int x, int y, SQUARE piece) ;

	// print checkerboard
	void print() ;
};

#endif