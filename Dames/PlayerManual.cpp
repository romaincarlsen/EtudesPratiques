#include "stdafx.h"
#include "PlayerManual.h"

//Create a manual player
PlayerManual::PlayerManual(int nbLinePiece, Checkerboard* board, DIRECTION direction) : Player(nbLinePiece, board, direction)
{
}


PlayerManual::~PlayerManual(void)
{
}

//Launch a game turn of a manual player
bool PlayerManual:: play(void)
{

	int x, y, xDest, yDest ;
	
	// board printing
	board->print() ;

	do {
		// piece selection
		cout << "select (ex : A1) :   " ;
		do {
			scanCoord(x, y) ;
		} while (!selectValid(x,y)) ;
		// destination square selection
		cout << "destination : (ex : A1) :   " ;
		do {
			scanCoord(xDest, yDest) ;
		} while (!destValid(xDest,yDest)) ;
	} while (!isMoveValid(board->getSquare()[x][y],x,y,xDest,yDest)) ;
	// move execution, return true if the player win the game
	return move(x,y,xDest,yDest) ;
}

//Init x and y value with user input
void PlayerManual::scanCoord(int & x, int & y) {
	string tmp ;
	do {
		// scan user input with format (ex : A1)
		cin >> tmp ;
		// convert input on x and y int values
		x = letter_to_num_column(tmp[0]) ;
		y = atoi(tmp.erase(0,1).c_str()) ;
	} while (x<=0 || x>board->getNbColumn() || y<=0 || y>board->getNbLine()) ;
	// transform x and y value for table indice
	x-- ;
	y-- ;
}