#ifndef PLAYERMANUAL_H
#define PLAYERMANUAL_H

#include "tools.h"

#include "player.h"

class PlayerManual :
	public Player
{

private:

	//Init x and y value with user input
	void scanCoord(int & x, int & y) ;

public:
	//Create a manual player
	PlayerManual(int nbLinePiece, Checkerboard* board, DIRECTION direction) ;
	~PlayerManual(void);
	//Launch a game turn of a manual player
	bool play(void);
};

#endif
