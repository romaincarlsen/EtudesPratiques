#include "Player.h"

//Create the player
Player::Player(int nbLinePiece, Checkerboard* board, DIRECTION direction)
{
	//Indicate direction of the offensive
	this->direction = direction ;
	//Indicate the board where players play
   // this->board = board ;

	
	// init pieces code in function of offensive direction
	if (this->direction == NORD) {
		this->king = WHITE_KING ;
		this->piece = WHITE_PIECE ;
		this->oppKing = BLACK_KING ;
		this->oppPiece = BLACK_PIECE ;
        this->state_select = WHITE_SELECT ;
        this->state_dest = WHITE_DEST ;
	}
	else {
		this->king = BLACK_KING ;
		this->piece = BLACK_PIECE ;
		this->oppKing = WHITE_KING ;
		this->oppPiece = WHITE_PIECE ;
        this->state_select = BLACK_SELECT ;
        this->state_dest = BLACK_DEST ;
	}
	// put player pieces
	int yy ;
	for (int y=0 ; y<nbLinePiece ; y++)
		for (int x=0 ; x<board->getSize() ; x++) {
			if (this->direction == NORD)
                yy = y ;
			else
                yy = board->getSize()-1-y ;
			board->putPiece(x, yy, this->piece);
			 
		}

}

Player::~Player(void)
{
}

QString Player::toString() {
    QString num = (isWhite() ? "1" : "2") ;
    return "player" + num ;
}

// indicate if y coordonate corresponde with king line of player
bool Player::isOnKingLineOnBoard(int yDest, Checkerboard* board) {
	if (direction==NORD)
		return yDest==board->getSize()-1 ;
	else
		return yDest==0 ;
}

int Player::theBestKillOnBoard(SQUARE piece, int x, int y, Checkerboard* board) {
    int best = 0 ;
    for (int xDest=0 ; xDest<board->getSize() ; xDest++) {
        for (int yDest=0 ; yDest<board->getSize() ; yDest++) {
            if (isMoveValidOnBoard(piece, x, y, xDest, yDest, board) && isKillOnBoard(piece, x, y, xDest, yDest, board)) {

                Checkerboard* copyBoard = new Checkerboard(board) ;
                moveOnBoard(x,y,xDest,yDest,copyBoard) ;
                qDebug() << "move from " << x << " " << y << " to " << xDest << " " << yDest << endl ;
                int nbKill = 1 + theBestKillOnBoard(piece, xDest, yDest, copyBoard) ;

                qDebug() << "kill " << nbKill << endl ;
                best = best<nbKill ? nbKill : best ;
                qDebug() << "best " << best << endl ;
                delete copyBoard ;

            }
        }
    }
    return best ;
}

bool Player::isTheBestKillOnBoard(SQUARE piece, int x, int y, int xDest, int yDest, Checkerboard* board) {
    if (isMoveValidOnBoard(piece, x, y, xDest, yDest, board) && isKillOnBoard(piece, x, y, xDest, yDest, board)){
        Checkerboard* copyBoard = new Checkerboard(board) ;
        moveOnBoard(x,y,xDest,yDest,copyBoard) ;
        int kill = 1 + theBestKillOnBoard(piece, xDest, yDest, copyBoard) ;

        qDebug() << "kill move chosen " << kill << endl ;

        for (int xt=0 ; xt<board->getSize() ; xt++) {
            for (int yt=0 ; yt<board->getSize() ; yt++) {
                if (theBestKillOnBoard(board->getSquare(xt,yt), xt, yt, board) > kill)
                    return false;
            }
        }
        delete copyBoard ;
    }
  return true ;
}

bool Player::canKillOnBoard(SQUARE piece, int x, int y, Checkerboard* board) const {
	int xDest ;
	int yDest ;
	if (isPiece(piece)) {
		for (int vx = -2 ; vx<=2 ; vx+=4)
			for (int vy = -2 ; vy<=2 ; vy+=4) {
				xDest = x+vx ;
				yDest = y+vy ;
                if (xDest>=0 && xDest<board->getSize() && yDest>=0 && yDest<board->getSize())
                    if (destValidOnBoard(xDest, yDest, board) && isMoveValidOnBoard(piece, x, y, xDest, yDest, board) && isKillOnBoard(piece, x, y, xDest, yDest, board))
						return true ;
			}
	}
	if (isKing(piece)) {
		for (int vx=-1 ; vx<=1 ; vx+=2)
			for (int vy=-1 ; vy<=1 ; vy+=2) {
				xDest = x ;
				yDest = y ;
				do {
                    if (destValidOnBoard(xDest, yDest, board) && isMoveValidOnBoard(piece, x, y, xDest, yDest, board) && isKillOnBoard(piece, x, y, xDest, yDest, board))
						return true ;							
					xDest+=vx ;
					yDest+=vy ;
                } while (xDest>=0 && xDest<board->getSize() && yDest>=0 && yDest<board->getSize()) ;
			}
	}
	return false ;
}

bool Player::haveKillOnBoard(Checkerboard* board) const {
    for (int x=0 ; x<board->getSize() ; x++)
        for (int y=0 ; y<board->getSize() ; y++)
            if (canKillOnBoard(board->getSquare(x,y), x, y, board))
				return true ;
	return false ;			 
}

bool Player::isWhite() const {
	return king == WHITE_KING && piece == WHITE_PIECE;
}

bool Player::isBlack() const {
	return king == BLACK_KING && piece == BLACK_PIECE ;
}

//Verify if the square selected contains a player piece
bool Player::selectValidOnBoard(int x, int y, Checkerboard* board) const{
    return isMine(board->getSquare(x,y)) ;
}

//Verify if the destination square selected is empty
bool Player::destValidOnBoard(int x, int y, Checkerboard* board) const{
    return board->getSquare(x,y) == EMPTY ;
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
void Player::scanNumberOfOnBoard(int & nbMinePiece, int & nbMineKing, int & nbOpponentPiece, int & nbOpponentKing, Checkerboard* board) {
	nbMinePiece = nbMineKing = nbOpponentPiece = nbOpponentKing = 0 ;
	SQUARE tmp ;
	for (int x=0 ; x<board->getSize() ; x++)
		for (int y=0 ; y<board->getSize() ; y++)
			if ((isEven(x) && isEven(y)) || (isOdd(x) && isOdd(y))){
                tmp = board->getSquare(x,y) ;
				nbMinePiece += tmp == piece ;
				nbMineKing += tmp == king ;
				nbOpponentPiece += tmp == oppPiece ;
				nbOpponentKing += tmp == oppKing ;
			}
}

//Kill the opponent piece
void Player::killOnBoard(int x,int y,int xDest,int yDest, Checkerboard* board) {
    for ( (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y-- ; x!=xDest && y!=yDest ; (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y--) {
        if (isPiece(board->getSquare(x,y)) || isKing(board->getSquare(x,y))) {
            board->setSquare(x,y, GHOST) ;
        }
    }
}

//Verify it's a valid piece move
bool Player::isPieceMoveOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const{
	return isMine(playerPiece) && isPiece(playerPiece) && (
			this->direction == NORD && yDest==y+1 && (xDest == x+1 || xDest==x-1)
			|| this->direction == SUD && yDest==y-1 && (xDest == x+1 || xDest==x-1)
			) ;
}

//Verify it's a valid piece kill
bool Player::isPieceKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const{
    return isMine(playerPiece) && isPiece(playerPiece) && (
            (yDest==y+2 || yDest==y-2) && (xDest == x+2 || xDest==x-2) && isOpponent(board->getSquare((x+xDest)/2,(y+yDest)/2))
			) ;
}

//Verify it's a valid king move
bool Player::isKingMoveOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const{
	if (!isKing(playerPiece) || !isMine(playerPiece))
		return false ;	
	int cpt = 0 ;
	//Loop for each square from piece to destination
	for ( (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y-- ; x!=xDest && y!=yDest ; (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y--)
        cpt += isNotEmpty(board->getSquare(x,y)) ;
	return cpt==0 ;
}

//Verify it's a valid king const
bool Player::isKingKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const{
	if (!isKing(playerPiece) || !isMine(playerPiece))
		return false ;
	int cpt = 0 ;
	int cptOpp = 0 ;
	//Loop for each square from piece to destination
	for ( (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y-- ; x!=xDest && y!=yDest ; (x-xDest)<0 ? x++ : x--, (y-yDest)<0 ? y++ : y--) {
        cpt += isMine(board->getSquare(x,y)) ;
        cptOpp += isOpponent(board->getSquare(x,y)) ;
	}
	return cpt==0 && cptOpp==1 ;
}

//Verify if the move is valid
bool Player::isMoveValidOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const{
    return  destValidOnBoard(xDest,yDest, board) &&
            (isPieceMoveOnBoard(playerPiece, x,y,xDest,yDest, board) || isPieceKillOnBoard(playerPiece, x,y,xDest,yDest, board)
            || isKingMoveOnBoard(playerPiece,x,y,xDest,yDest, board) || isKingKillOnBoard(playerPiece,x,y,xDest,yDest, board)) ;
}

//Verify if the move is a kill
bool Player::isKillOnBoard(SQUARE playerPiece, int x, int y, int xDest, int yDest, Checkerboard* board) const{
    return isPieceKillOnBoard(playerPiece,x,y,xDest,yDest, board) || isKingKillOnBoard(playerPiece,x,y,xDest,yDest, board) ;
}

//Execute the move
bool Player::moveOnBoard(int x, int y, int xDest, int yDest, Checkerboard * board) {
	int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
	// swap selected piece square and destination square
	
    SQUARE playerPiece = board->getSquare(x,y) ;
    //board->getSquare(x,y) = board->getSquare(xDest,yDest) ;
    //board->getSquare(xDest,yDest) = playerPiece ;
    board->setSquare(xDest, yDest, playerPiece);
    board->setSquare(x, y, EMPTY);
    if (isKillOnBoard(playerPiece,x,y,xDest,yDest,board)) {
        killOnBoard (x, y, xDest, yDest, board) ;
        scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
		return nbOpponentPiece+nbOpponentKing == 0 ;
	}
	return false ;
}
