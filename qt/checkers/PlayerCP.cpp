#include "PlayerCP.h"


//create a CP player
PlayerCP::PlayerCP(int nbLinePiece, Checkerboard* board, DIRECTION direction, int level) : Player(nbLinePiece, board, direction)
{_level=level;
}


PlayerCP::~PlayerCP(void)
{
}

bool PlayerCP::isCP() {
    return true ;
}

int PlayerCP::costFunction(Checkerboard board) {
    return 42;
}

std::vector<MOVE> PlayerCP::findMoveOnBoard(Checkerboard* board, COLOR color) {
	std::vector<MOVE> m ;
    m.resize(0);
    for (int x=0 ; x<board->getSize() ; x++) {
        for (int y=0 ; y<board->getSize() ; y++) {
            if (Tools::isWhite(board->getSquare(x,y)) && color==WHITE || Tools::isBlack(board->getSquare(x,y)) && color==BLACK) {
                if (selectValidOnBoard(x,y, board)) {
                    for (int xDest=0 ; xDest<board->getSize() ; xDest++) {
                        for (int yDest=0 ; yDest<board->getSize() ; yDest++) {
                            bool canKill = haveKillOnBoard(board) ;
                            if (isMoveValidOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board)) {
                                bool wasKill = isKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest,board) ;
                                if (!(canKill && !wasKill)) {
                                    if (!wasKill || isTheBestKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board)){
                                        m.resize(m.size()+1);
                                        MOVE move ;
                                        move.x = x ;
                                        move.y = y ;
                                        move.xDest = xDest ;
                                        move.yDest = yDest ;
                                        m[m.size()-1] = move ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
	return m ;
}

Checkerboard PlayerCP::applyMove(Checkerboard board, MOVE m) {
	Checkerboard c(10) ;
	return c ;
}

int PlayerCP::getLevel() {
    return _level ;
}

int PlayerCP::negaMax(Checkerboard* board, int depth, COLOR color, MOVE & best) {

    if (depth==0 || board->isWin()){
        return (int)color * costFunction(board);
    }
    std::vector<MOVE> move = findMoveOnBoard(board,color) ;
    foreach(MOVE m , move){
        qDebug() << m.x << " " << m.y << " " << m.xDest << " " << m.yDest << endl ;
    }

    return 42 ;

	//function negamax(node, depth, color)
    //if depth = 0 or node is a terminal node
    //    return color * the heuristic value of node
    //bestValue := -infini
    //foreach child of node
    //    val := -negamax(child, depth - 1, -color)
    //    bestValue := max( bestValue, val )
    //return bestValue
	//
	//Initial call for Player A's root node
	//rootNodeValue := negamax( rootNode, depth, 1)
	//
	//Initial call for Player B's root node
	//rootNodeValue := -negamax( rootNode, depth, -1)

    /*MOVEVALUE mv ;*/


}
