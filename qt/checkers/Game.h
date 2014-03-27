#ifndef GAME_H
#define GAME_H

#include "include.h"

#include "Checkerboard.h"
#include "Player.h"
#include "PlayerCP.h"
#include "PlayerManual.h"

class Game
{

private:
    Player* P1 ;
    Player* P2 ;
    Checkerboard* board ;
public:
    // create game with dimension parameters
    Game(int size, int nbLinePiece1, int nbLinePiece2);
    ~Game();
    //launch the game
    void launch();
    // print game
    void print() ;
};

#endif
