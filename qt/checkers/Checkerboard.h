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
typedef std::vector<std::vector<QSQUARE>> Damier;

class Checkerboard
{

private:
	int _size ;
	Damier _square;
    //attributs contenant la position de la case sélectionnée
    Selection selection;
public:
	// create checkerboard with dimension parameters
	Checkerboard(int size);
    Checkerboard(Checkerboard* board);
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

    //Permet de changer la case sélectionnée
    void select(int x, int y);
    //déselectionne la case
    void deselect();

	// print checkerboard
    QString toString() ;

    void paint(QGridLayout* board_gl) ;

    //affiche la case sélectionnée
    void printSelect(QGridLayout *board_gl);
};

#endif
