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
	bool valid ;
	bool canKill = haveKillOn(*board) ;
	bool wasKill ;
	// board printing
	board->print() ;

	do {
		// piece selection
		cout << "select (ex : A1) :   " ;
		do {
			scanCoord(x, y) ;
			valid = selectValid(x,y) ;
		} while (!valid) ;
		// destination square selection
		cout << "destination : (ex : A1) :   " ;
		do {
			scanCoord(xDest, yDest) ;
			valid = destValid(xDest,yDest) ;
		} while (!valid) ;
		if(valid = isMoveValid(board->getSquare()[x][y],x,y,xDest,yDest)) {
			wasKill = isKill(board->getSquare()[x][y],x,y,xDest,yDest) ;
			if(!(valid=!(canKill && !wasKill)))
					cout << endl << "You have to kill !" << endl << endl ;
		}
	} while (!valid) ;

	// move execution, return true if the player win the game
	if(move(x,y,xDest,yDest))
		return true ;
	else {
		while (wasKill && canKillOn(board->getSquare()[xDest][yDest], xDest, yDest, *board)) {
			x = xDest ;
			y = yDest ;
			cout << "next destination : (ex : A1) :   " ;
			do {
				scanCoord(xDest, yDest) ;
				valid = destValid(xDest,yDest) && isMoveValid(board->getSquare()[x][y],x,y,xDest,yDest) && (wasKill = isKill(board->getSquare()[x][y],x,y,xDest,yDest)) ;
			} while (!valid) ;
			if(move(x,y,xDest,yDest))
				return true ;
		}
		if (isPiece(board->getSquare()[xDest][yDest]) && isOnKingLine(yDest))
			board->setSquare(xDest, yDest, king);
	}
	return false ;
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
	} while (x<=0 || x>board->getSize() || y<=0 || y>board->getSize()) ;
	// transform x and y value for table indice
	x-- ;
	y-- ;
}