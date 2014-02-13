#pragma once

#include "Checkerboard.h"
#include "Player.h"
#include "Square.h"
#include "Tools.h"

class Game
{

private:
	Player P1 ;
	Player P2 ;
	Checkerboard* board ;
public:
	// create game with dimension parameters
	Game(int nbLine, int nbColumn);
	~Game(void);
	// print game
	void print() ;
};

