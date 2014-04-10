#ifndef PLAYER_H
#define PLAYER_H

#include "include.h"
#include "Tools.h"
#include "struct.h"
#include "Checkerboard.h"


class Player
{

public:
	//Indicate direction of the offensive
	DIRECTION direction ;

  /*  Checkerboard* board ;*/
	//Indicate how is coded the player king
	SQUARE king ;
	//Indicate how is coded the player piece
	SQUARE piece ;
	//Indicate how is coded the opponent king
	SQUARE oppKing ;
	//Indicate how is coded the opponent piece
	SQUARE oppPiece ;

    STATE state_select ;
    STATE state_dest ;

    QString toString() ;

    int x ;
    int y ;
    int xDest ;
    int yDest ;

	// indicate if y coordonate corresponde with king line of player
    bool isOnKingLineOnBoard(int yDest, Checkerboard* board) ;

    int theBestKillOnBoard(SQUARE piece, int x, int y, Checkerboard* board, int best=0) ;

    bool isTheBestKillOnBoard(SQUARE piece, int x, int y,int xDest, int yDest, Checkerboard* board) ;

    bool canKillOnBoard(SQUARE piece, int x, int y, Checkerboard* board) const ;

    bool haveKillOnBoard(Checkerboard* board) const ;

	bool isWhite() const ;

	bool isBlack() const ;

	//Verify if the square selected contains a player piece
    bool selectValidOnBoard(int x, int y, Checkerboard* board) const;

	//Verify if the destination square selected is empty
    bool destValidOnBoard(int x, int y, Checkerboard* board) const;

	//Verify if the square selected is at the player
	bool isMine(SQUARE square) const;

	//Verify if the square selected is at the opponent
	bool isOpponent(SQUARE square) const;

	//Count the number of differents types of pieces
    void scanNumberOfOnBoard(int & nbMinePiece, int & nbMineKing, int & nbOpponentPiece, int & nbOpponentKing, Checkerboard* board) ;

	//Kill the opponent piece
    void killOnBoard(int x,int y,int xDest,int yDest, Checkerboard* board);
	
	//Verify it's a valid piece move
    bool isPieceMoveOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const;

	//Verify it's a valid piece kill
    bool isPieceKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const;

	//Verify it's a valid king move
    bool isKingMoveOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const;

	//Verify it's a valid king kill
    bool isKingKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const;

	//Verify if the move is valid
    bool isMoveValidOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const;

	//Verify if the move is a kill
    bool isKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const;


	//Execute the move
    bool moveOnBoard(int x, int y, int xDest, int yDest, Checkerboard * board) ;

	//Create the player
    Player(int nbLinePiece, Checkerboard* board, DIRECTION direction);

	~Player(void);

	//Abstract function implements play method in function of the player (CP or Manual) 
	virtual bool play() = 0;
};

#endif
