#pragma once
#include "Piece.h"
#include "Player.h"
#include "Square.h"
class Checker :
	public Piece
{

private:

	Player player ;
	Square onSquare ;

public:
	Checker(void);
	~Checker(void);
};

