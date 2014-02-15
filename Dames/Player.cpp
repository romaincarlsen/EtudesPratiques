#include "stdafx.h"
#include "Player.h"

//Create the player
Player::Player(int nbLinePiece, Checkerboard* board, DIRECTION direction)
{
	//Indicate direction of the offensive
	this->direction = direction ;
	//Indicate the board where players play
	this->board = board ;
	
	// init pieces code in function of offensive direction
	if (this->direction == NORD) {
		this->king = WHITE_KING ;
		this->piece = WHITE_PIECE ;
		this->oppKing = BLACK_KING ;
		this->oppPiece = BLACK_PIECE ;
	}
	else {
		this->king = BLACK_KING ;
		this->piece = BLACK_PIECE ;
		this->oppKing = WHITE_KING ;
		this->oppPiece = WHITE_PIECE ;
	}
	// put player pieces
	int yy ;
	for (int y=0 ; y<nbLinePiece ; y++)
		for (int x=0 ; x<board->getNbColumn() ; x++) {
			if (this->direction == NORD)
				yy = y ;
			else
				yy = board->getNbLine()-1-y ;
			board->putPiece(x, yy, this->piece);
			 
		}

}

Player::~Player(void)
{
}

//Verify if the square selected contains a player piece
bool Player::selectValid(int x, int y) {
	return board->getSquare()[x][y] == king || board->getSquare()[x][y] == piece ;
}

//Verify if the destination square selected is empty
bool Player::destValid(int x, int y) {
	return board->getSquare()[x][y] == EMPTY ;
}

//Verify if the move would take an opponent piece
bool Player::isKill(int x,int y,int xDest,int yDest) {
	SQUARE kill = board->getSquare()[(x+xDest)/2][(y+yDest)/2] ;
	return kill == oppKing || kill == oppPiece ;
}

//Verify if the move is valid
bool Player::moveValid(int x, int y, int xDest, int yDest) {

	switch(board->getSquare()[x][y]){
		case WHITE_PIECE :		// simple move test
								if(yDest==y+1 && (xDest == x+1 || xDest==x-1))
									return true;
								// kill move test
								if(yDest==y+2 && (xDest == x+2 || xDest==x-2))
									return isKill(x,y,xDest,yDest);
								break;
		case BLACK_PIECE :		// simple move test
								if(yDest==y-1 && (xDest == x+1 || xDest==x-1))
									return true;
								// kill move test
								if(yDest==y-2 && (xDest == x+2 || xDest==x-2))
									return isKill(x,y,xDest,yDest);
								break;
		case WHITE_KING :	// test if king move is diagonal
							return(xDest-x) == (yDest-y);
							break;
		case BLACK_KING :	// test if king move is diagonal
							return (xDest-x) == (yDest-y);
							break ;
	}
	return false;
}

//Execute the move
void Player::move(int x, int y, int xDest, int yDest) {
	// swap selected piece square and destination square
	SQUARE tmp = board->getSquare()[x][y] ;
	board->getSquare()[x][y] = board->getSquare()[xDest][yDest] ;
	board->getSquare()[xDest][yDest] = tmp ;
}
