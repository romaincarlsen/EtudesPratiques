#include "PlayerCP.h"


//create a CP player
PlayerCP::PlayerCP(int nbLinePiece, Checkerboard* board, DIRECTION direction) : Player(nbLinePiece, board, direction)
{
}


PlayerCP::~PlayerCP(void)
{
}


int PlayerCP::costFunction(Checkerboard board) {
	return 42 ;
}

std::vector<MOVE> PlayerCP::findMove(Checkerboard board, COLOR color) {
	std::vector<MOVE> m ;
	return m ;
}

Checkerboard PlayerCP::applyMove(Checkerboard board, MOVE m) {
	Checkerboard c(10) ;
	return c ;
}

MOVEVALUE PlayerCP::negaMax(Checkerboard board, int depth, COLOR color) {

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

	MOVEVALUE mv ;

    if (depth = 0 || board.isWin()) {
		MOVE m ;
		m.x = m.y = m.xDest = m.yDest = -1 ;
		mv.m = m ;
		mv.value = color * costFunction(board) ;
        return  mv ;
	}
	MOVEVALUE tmp ;
	std::vector<MOVE> listMove = findMove(board,color) ;
	std::vector<MOVE>::iterator it = listMove.begin() ;
	if (it != listMove.end()) {
        tmp = negaMax(applyMove(board,*it), depth - 1, (COLOR)-color) ;
		tmp.m = *it ;
		tmp.value *= -1 ;
		mv = tmp ;
		++it ;
	}
	for (it ; it != listMove.end(); ++it) {
        tmp = negaMax(applyMove(board,*it), depth - 1, (COLOR)-color) ;
		tmp.m = *it ;
		tmp.value *= -1 ;
		mv = tmp.value > mv.value ? tmp : mv ;
	}
    return mv ;
}


//Launch a game turn of a CP player
bool PlayerCP::play(void) {
/*
	COLOR color = isWhite() ? WHITE : BLACK ;
	MOVEVALUE mv = negaMax(*board, 10, color) ;
	mv.value *= color ;

    return moveOnBoard(mv.m.x, mv.m.y, mv.m.xDest, mv.m.yDest, board) ;*/
    return false;
}

