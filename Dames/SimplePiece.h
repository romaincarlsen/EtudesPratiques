#pragma once
#include "Piece.h"
#include "Player.h"
#include "Square.h"

class SimplePiece :
	public Piece
{

private:

		Player player ;
		Square onSquare ;

public:
	SimplePiece(void);
	~SimplePiece(void);
};

