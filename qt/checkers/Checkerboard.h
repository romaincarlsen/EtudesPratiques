#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>

#include "include.h"
#include "struct.h"
#include "Tools.h"
#include "labelcase.h"

// structure corresponding with current piece selected
typedef struct {
    int x ;
    int y ;
    bool select;
} Selection ;

class Checkerboard
{
private:
    // cherckerboard size ( = nb columns = nb lines)
	int _size ;
    // checkerboard squares with type struct QSQUARE
	Damier _square;
public:
    Checkerboard() ;
    // create checkerboard with dimension parameters
    Checkerboard(int size);
    // create a copy of the checkerboard
    Checkerboard(const Checkerboard & board);
	~Checkerboard(void);
    //attributs contenant la position de la case sélectionnée
    Selection selection;
	int getSize() const;
    // set the enum square a the coordinate x y with the value
    void setSquare(int x, int y, SQUARE value);
    Damier getQSquare() const ;
    // return the square at coordonate x y
    QSQUARE getQSquare(int x, int y) const ;
    // return the enum SQUARE of the square at coordonate x y
    SQUARE getSquare(int x, int y) const ;
    // put Piece on the Checkerboard
	bool putPiece(int x, int y, SQUARE piece) ;
	// delete pieces which have been killed during last turn
	void ghostBuster() ;
    // indicate if there is a current move
    // corresponding with the kill of some pieces
    // return true if there is a ghost square on the board
    bool moveBegined() ;
	// indicate if the checkerboard have a winner (if one player haven't pieces)
	bool isWin() const ;
    //Permet de changer la case sélectionnée
    void select(int x, int y);
    //déselectionne la case
    bool deselect();
    // return the board with caracters format
    string toString() const ;
};
#else
class Checkerboard;
#endif
