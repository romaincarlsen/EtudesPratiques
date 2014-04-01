#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>

#include "include.h"

#include "struct.h"
#include "Tools.h"

typedef std::vector<std::vector<SQUARE>> Damier;

class Checkerboard
{

private:
	int _size ;
	//SQUARE** square ;
	Damier _square;
public:
	// create checkerboard with dimension parameters
	Checkerboard(int size);
	~Checkerboard(void);

	int getSize() const;

	void setSquare(int x, int y, SQUARE square);

	//SQUARE** getSquare() ;
	const Damier& getSquare() const;
	// put Piece on the Checkerboard
	bool putPiece(int x, int y, SQUARE piece) ;

	// delete pieces which have been killed during last turn
	void ghostBuster() ;

	// indicate if the checkerboard have a winner (if one player haven't pieces)
	bool isWin() const ;

	// print checkerboard
    QString toString() ;
};

#endif
