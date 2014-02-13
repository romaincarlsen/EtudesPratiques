#pragma once
#include "Square.h"
#include "Tools.h"

class Checkerboard
{

private:
	int nbColumn ;
	int nbLine ;
	int** square ;
public:
	// create checkerboard with dimension parameters
	Checkerboard(int nbLine, int nbColumn);
	~Checkerboard(void);
	// print checkerboard
	void print() ;
};

