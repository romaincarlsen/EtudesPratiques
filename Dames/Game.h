#ifndef GAME_H
#define GAME_H

#include "tools.h"

#include "Checkerboard.h"
#include "Player.h"
#include "PlayerManual.h"
#include "PlayerCP.h" ;

class Game
{

private:
	Player* P1 ;
	Player* P2 ;
	Checkerboard* board ;
public:
	// create game with dimension parameters
	Game(int nbLine, int nbColumn, int nbLinePiece1, int nbLinePiece2);
	~Game(void);
	//launch the game
	void launch();
	// print game
	void print() ;
};

#endif