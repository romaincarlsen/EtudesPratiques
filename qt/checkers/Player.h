#ifndef PLAYER_H
#define PLAYER_H

#include "include.h"

#include "struct.h"
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

	// indicate if y coordonate corresponde with king line of player
	bool isOnKingLine(int yDest) ;

	bool canKillOn(SQUARE piece, int x, int y, Checkerboard board) const ;

	bool haveKillOn(Checkerboard board) const ;

	bool isWhite() const ;

	bool isBlack() const ;

	//Verify if the square selected contains a player piece
	bool selectValid(int x, int y) const;

	//Verify if the destination square selected is empty
	bool destValid(int x, int y) const;

	//Verify if the square selected is at the player
	bool isMine(SQUARE square) const;

	//Verify if the square selected is at the opponent
	bool isOpponent(SQUARE square) const;

	//Count the number of differents types of pieces
	void scanNumberOf(int & nbMinePiece, int & nbMineKing, int & nbOpponentPiece, int & nbOpponentKing) ;

	//Kill the opponent piece
	void kill(int x,int y,int xDest,int yDest);
	
	//Verify it's a valid piece move
	bool isPieceMove(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;

	//Verify it's a valid piece kill
	bool isPieceKill(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;

	//Verify it's a valid king move
	bool isKingMove(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;

	//Verify it's a valid king kill
	bool isKingKill(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;

	//Verify if the move is valid
	bool isMoveValid(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;

	//Verify if the move is a kill
	bool isKill(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;


	//Execute the move
	bool move(int x, int y, int xDest, int yDest) ;

public:

	//Create the player
	Player(int nbLinePiece, Checkerboard* board, DIRECTION direction);

	~Player(void);

	//Abstract function implements play method in function of the player (CP or Manual) 
	virtual bool play() = 0;
};

#endif
