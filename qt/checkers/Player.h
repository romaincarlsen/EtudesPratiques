#ifndef PLAYER_H
#define PLAYER_H

#include "include.h"
#include "Tools.h"
#include "struct.h"
#include "Checkerboard.h"

class Player
{

public:
    // level of the player for computer players
    int level ;
    // numero of the costfunction of the player for computer players
    int costFunction;
	//Indicate direction of the offensive
	DIRECTION direction ;
	//Indicate how is coded the player king
	SQUARE king ;
	//Indicate how is coded the player piece
	SQUARE piece ;
	//Indicate how is coded the opponent king
	SQUARE oppKing ;
	//Indicate how is coded the opponent piece
	SQUARE oppPiece ;
    // the enum STATE when the player have to select a piece
    STATE state_select ;
    // the enum STATE when the player have to select a destination
    STATE state_dest ;
    // string informations about the player
    QString toString() ;
    // coordonate of the piece that the player decided to move
    int x ;
    int y ;
    // coordonate of the square where the player decided to move his piece
    int xDest ;
    int yDest ;
    int getLevel() ;
    // return true if the player is a computer
    bool isCP() ;
	// indicate if y coordonate corresponde with king line of player
    bool isOnKingLineOnBoard(int yDest, const Checkerboard & board) ;
    // return the number maximum of piece that the player can kill from x y square on the board in parameter
    int theBestKillOnBoard(SQUARE piece, int x, int y, const Checkerboard & board, bool with_thread) ;
    // return true if the destination xDest yDest square chosen by player is one or is the begin of one of the best kill he can do
    bool isTheBestKillOnBoard(SQUARE piece, int x, int y,int xDest, int yDest, const Checkerboard & board, bool with_thread) ;
    // return true if the player can kill an opponent piece from x y square with the piece indicate
    bool canKillOnBoard(SQUARE piece, int x, int y, const Checkerboard & board) const ;
    // return true if the player can kill an opponenet piece on the board
    bool haveKillOnBoard(const Checkerboard & board) const ;
    // return true is the player is white
	bool isWhite() const ;
    // return true if the player is black
	bool isBlack() const ;
	//Verify if the square selected contains a player piece
    bool selectValidOnBoard(int x, int y, const Checkerboard & board) const;
	//Verify if the destination square selected is empty
    bool destValidOnBoard(int x, int y, const Checkerboard & board) const;
	//Verify if the square selected is at the player
	bool isMine(SQUARE square) const;
	//Verify if the square selected is at the opponent
	bool isOpponent(SQUARE square) const;
	//Count the number of differents types of pieces
    void scanNumberOfOnBoard(int & nbMinePiece, int & nbMineKing, int & nbOpponentPiece, int & nbOpponentKing, const Checkerboard & board) ;
	//Kill the opponent piece
    void killOnBoard(int x,int y,int xDest,int yDest, Checkerboard & board);
	//Verify it's a valid piece move
    bool isPieceMove(SQUARE playerPiece, int x, int y, int xDest, int yDest) const;
	//Verify it's a valid piece kill
    bool isPieceKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, const Checkerboard & board) const;
	//Verify it's a valid king move
    bool isKingMoveOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, const Checkerboard & board) const;
	//Verify it's a valid king kill
    bool isKingKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, const Checkerboard & board) const;
	//Verify if the move is valid
    bool isMoveValidOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, const Checkerboard & board) const;
	//Verify if the move is a kill
    bool isKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, const Checkerboard & board) const;
	//Execute the move
    bool moveOnBoard(int x, int y, int xDest, int yDest, Checkerboard & board) ;
	//Create the player
    Player() ;
    Player(int nbLinePiece, Checkerboard & board, DIRECTION direction, int level = -1);
	~Player(void);
};
#else
class Player ;
#endif
