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
	Checkerboard checkerboard ;
public:
	Game(void);
	~Game(void);
};

