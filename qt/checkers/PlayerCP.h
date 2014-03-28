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
	
	int costFunction(Checkerboard board) ;

	std::vector<MOVE> findMove(Checkerboard board, COLOR color) ;

	Checkerboard applyMove(Checkerboard board, MOVE m) ;

	MOVEVALUE negaMax(Checkerboard board, int depth, COLOR color) ;

	
public:
	//create a CP player
    PlayerCP(int nbLinePiece,Checkerboard* board, DIRECTION direction) ;
	~PlayerCP(void);
	//Launch a game turn of a CP player
	bool play(void);
};

#endif
