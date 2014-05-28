#ifndef TOOLS_H
#define TOOLS_H

#include "include.h"

#include "struct.h"

class Tools
{

public:

static bool isWhite(const SQUARE square) ;

static bool isBlack(const SQUARE square) ;

// return if val is even number
static bool isEven(int val) ;

// return if val is odd number
static bool isOdd(int val) ;

// return if the square contain a king
static bool isKing(SQUARE square);

// return if the square contain a piece
static bool isPiece(SQUARE square);

// return if the square is occuped
static bool isNotEmpty(SQUARE square) ;

// return if square is locked (white square)
static bool isLocked(SQUARE square) ;

// return char corresponding to square type for consol printing
static char square_to_char(SQUARE square) ;

// return img corresponding to square type for consol printing
static QPixmap square_to_img(SQUARE square) ;

static double timediff(timeval begin, timeval end) ;

};

#endif
