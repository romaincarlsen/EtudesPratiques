#include "stdafx.h"
#include "Game.h"

// create game with dimension parameters
Game::Game(int nbLine, int nbColumn)
{
		// init board
		board = new Checkerboard(nbLine, nbColumn) ;
}


Game::~Game(void)
{
		delete board ;
}

// print game
void Game::print(void)
{
		board->print() ;
}
