#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include "tools.h"
#include "Checkerboard.h"

class Player
{

protected:
	//Indicate direction of the offensive
	DIRECTION direction ;
	//Indicate the board where players play
	Checkerboard* board ;
	//Indicate how is coded the player king
	SQUARE king ;
	//Indicate how is coded the player piece
	SQUARE piece ;
	//Indicate how is coded the opponent king
	SQUARE oppKing ;
	//Indicate how is coded the opponent piece
	SQUARE oppPiece ;

public:
	//Create the player
	Player(int nbLinePiece, Checkerboard* board, DIRECTION direction);

	~Player(void);

	//Verify if the square selected contains a player piece
	bool selectValid(int x, int y) ;

	//Verify if the destination square selected is empty
	bool destValid(int x, int y) ;

	//Verify if the move would take an opponent piece
	bool isKill(int x,int y,int xDest,int yDest) ;

	//Verify if the move is valid
	bool moveValid(int x, int y, int xDest, int yDest) ;

	//Execute the move
	void move(int x, int y, int xDest, int yDest) ;

	//Abstract function implements play method in function of the player (CP or Manual) 
	virtual bool play() = 0;
};

#endif
