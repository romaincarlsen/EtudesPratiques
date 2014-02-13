#pragma once
#include "Player.h"
#include "Piece.h"

class PlayerCP :
	public Player
{

private:

	Piece piece[NBPIECESPLAYERS] ;

public:
	PlayerCP(void);
	~PlayerCP(void);
};

