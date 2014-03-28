#include "PlayerManual.h"

//Create a manual player
PlayerManual::PlayerManual(int nbLinePiece, Checkerboard* board, DIRECTION direction) : Player(nbLinePiece, board, direction)
{
}


PlayerManual::~PlayerManual(void)
{
}

//Launch a game turn of a manual player
bool PlayerManual:: play(void)
{
    return true ;
}
