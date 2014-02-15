#ifndef PLAYERCP_H
#define PLAYERCP_H

#include "tools.h"

#include "Player.h"

class PlayerCP :
	public Player
{

private:

public:
	//create a CP player
	PlayerCP(int nbLinePiece, Checkerboard* board, DIRECTION direction) ;
	~PlayerCP(void);
};

#endif
