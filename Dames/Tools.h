#ifndef TOOLS_H
#define TOOLS_H

#include "main.h"

// return if val is even number
bool isEven(int val) ;

// return if val is odd number
bool isOdd(int val) ;

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