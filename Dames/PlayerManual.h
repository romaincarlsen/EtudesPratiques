#pragma once
#include "player.h"
#include "piece.h"
class PlayerManual :
	public Player
{

private:

	Piece piece[NBPIECESPLAYERS] ;

public:
	PlayerManual(void);
	~PlayerManual(void);
};

