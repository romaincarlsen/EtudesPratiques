#pragma once
#include "Square.h"
#include "Tools.h"

class Checkerboard
{

private:
	Square square[NBCOLUMN][NBLINE] ;

public:
	Checkerboard(void);
	~Checkerboard(void);
};

