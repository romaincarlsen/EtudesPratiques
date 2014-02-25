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
bool Player::selectValid(int x, int y) const{
	return isMine(board->getSquare()[x][y]) ;
}

//Verify if the destination square selected is empty
bool Player::destValid(int x, int y) const{
	return board->getSquare()[x][y] == EMPTY ;
}

//Verify if the square selected is at the player
bool Player::isMine(SQUARE square) const{
	return square == piece || square == king  ;
}

//Verify if the square selected is at the opponent
bool Player::isOpponent(SQUARE square) const{
	return square == oppPiece || square == oppKing  ;
}

//Count the number of differents types of pieces
void Player::scanNumberOf(int & nbMinePiece, int & nbMineKing, int & nbOpponentPiece, int & nbOpponentKing) {
	nbMinePiece = nbMineKing = nbOpponentPiece = nbOpponentKing = 0 ;
	SQUARE tmp ;
	for (int x=0 ; x<board->getNbColumn() ; x++)
		for (int y=0 ; y<board->getNbLine() ; y++)
			if ((isEven(x) && isEven(y)) || (isOdd(x) && isOdd(y))){
				tmp = board->getSquare()[x][y] ;
				nbMinePiece += tmp == piece ;
				nbMineKing += tmp == king ;
				nbOpponentPiece += tmp == oppPiece ;
				nbOpponentKing += tmp == oppKing ;
			}
}

//Kill the opponent piece
void Player::kill(int x,int y,int xDest,int yDest) {
	for ( (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y-- ; x!=xDest && y!=yDest ; (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y--)
		board->setSquare(x,y, EMPTY) ;
}

//Verify it's a valid piece move
bool Player::isPieceMove(SQUARE playerPiece, int x, int y, int xDest, int yDest) const{
	return isPiece(playerPiece) && (
			this->direction == NORD && yDest==y+1 && (xDest == x+1 || xDest==x-1)
			|| this->direction == SUD && yDest==y-1 && (xDest == x+1 || xDest==x-1)
			) ;
}

//Verify it's a valid piece kill
bool Player::isPieceKill(SQUARE playerPiece, int x, int y, int xDest, int yDest) const{
	return isPiece(playerPiece) && (
			(yDest==y+2 || yDest==y-2) && (xDest == x+2 || xDest==x-2) && isOpponent(board->getSquare()[(x+xDest)/2][(y+yDest)/2])
			) ;
}

//Verify it's a valid king move
bool Player::isKingMove(SQUARE playerPiece, int x, int y, int xDest, int yDest) const{
	if (!isKing(playerPiece))
		return false ;	
	int cpt = 0 ;
	//Loop for each square from piece to destination
	for ( (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y-- ; x!=xDest && y!=yDest ; (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y--)
		cpt += isNotEmpty(board->getSquare()[x][y]) ;
	return cpt==0 ;
}

//Verify it's a valid king const
bool Player::isKingKill(SQUARE playerPiece, int x, int y, int xDest, int yDest) const{
	if (!isKing(playerPiece))
		return false ;
	int cpt = 0 ;
	int cptOpp = 0 ;
	//Loop for each square from piece to destination
	for ( (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y-- ; x!=xDest && y!=yDest ; (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y--) {
		cpt += isMine(board->getSquare()[x][y]) ;
		cptOpp += isOpponent(board->getSquare()[x][y]) ;
	}
	return cpt==0 && cptOpp==1 ;
}

//Verify if the move is valid
bool Player::isMoveValid(SQUARE playerPiece, int x, int y, int xDest, int yDest) const{
	return  isPieceMove(playerPiece, x,y,xDest,yDest) || isPieceKill(playerPiece, x,y,xDest,yDest)
			|| isKingMove(playerPiece,x,y,xDest,yDest) || isKingKill(playerPiece,x,y,xDest,yDest) ;
}

//Verify if the move is a kill
bool Player::isKill(SQUARE playerPiece, int x, int y, int xDest, int yDest) const{
	return isPieceKill(playerPiece,x,y,xDest,yDest) || isKingKill(playerPiece,x,y,xDest,yDest) ;
}

//Execute the move
bool Player::move(int x, int y, int xDest, int yDest) {
	bool win = false ;
	int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
	// swap selected piece square and destination square
	
	SQUARE playerPiece = board->getSquare()[x][y] ;
	//board->getSquare()[x][y] = board->getSquare()[xDest][yDest] ;
	//board->getSquare()[xDest][yDest] = playerPiece ;
	board->setSquare(xDest, yDest, playerPiece);
	board->setSquare(x, y, EMPTY);
	if (isKill(playerPiece,x,y,xDest,yDest)) {
		kill (x, y, xDest, yDest) ;
		scanNumberOf(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing) ;
		return nbOpponentPiece+nbOpponentKing == 0 ;
	}
	return false ;
}
