#ifndef PLAYERCP_H
#define PLAYERCP_H

#include "include.h"
#include "Tools.h"
#include "struct.h"
#include "Checkerboard.h"
#include "Player.h"


class PlayerCP :
	public Player
{

private:
    int _level;

	int costFunction(Checkerboard board) ;

    std::vector<MOVE> findMoveOnBoard(Checkerboard* board, COLOR color) ;

	Checkerboard applyMove(Checkerboard board, MOVE m) ;

public:
	//create a CP player
    PlayerCP(int nbLinePiece,Checkerboard* board, DIRECTION direction, int level) ;
	~PlayerCP(void);

    int getLevel() ;

    bool isCP() ;

    int negaMax(Checkerboard* board, int depth, COLOR color, MOVE& best) ;

};

#endif
