#ifndef TOOLS_H
#define TOOLS_H

#include "include.h"

#include "struct.h"

bool isWhite(SQUARE square) ;

bool isBlack(SQUARE square) ;

// return if val is even number
bool isEven(int val) ;

// return if val is odd number
bool isOdd(int val) ;

// return if the square contain a king
bool isKing(SQUARE square);

// return if the square contain a piece
bool isPiece(SQUARE square);

// return if the square is occuped
bool isNotEmpty(SQUARE square) ;

// return if square is locked (white square)
bool isLocked(SQUARE square) ;

// return char corresponding to square type for consol printing
char square_to_char(SQUARE square) ;

// return column letter corresponding to column number for consol printing
char num_to_letter_column(int num) ;

//return column number corresponding to column letter for consol printing
int letter_to_num_column(char letter) ;

// scan int value on keyboard unless 0
int scanInt() ;


#endif
