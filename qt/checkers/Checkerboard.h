#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>

#include "include.h"

#include "struct.h"
#include "Tools.h"
#include "labelcase.h"
typedef struct {

    int x ;
    int y ;
    bool select;
} Selection ;


class Checkerboard
{

private:
	int _size ;
	Damier _square;

public:
	// create checkerboard with dimension parameters
	Checkerboard(int size);
    Checkerboard(Checkerboard* board);
	~Checkerboard(void);

    //attributs contenant la position de la case sélectionnée
    Selection selection;

	int getSize() const;

	void setSquare(int x, int y, SQUARE square);

    Damier getQSquare() const ;

    QSQUARE getQSquare(int x, int y) const ;

    SQUARE getSquare(int x, int y) const ;

    // put Piece on the Checkerboard
	bool putPiece(int x, int y, SQUARE piece) ;

	// delete pieces which have been killed during last turn
	void ghostBuster() ;

    bool moveBegined() ;

	// indicate if the checkerboard have a winner (if one player haven't pieces)
	bool isWin() const ;

    //Permet de changer la case sélectionnée
    void select(int x, int y);
    //déselectionne la case
    bool deselect();
    string toString();

};

#endif
