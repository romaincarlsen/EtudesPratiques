#ifndef STRUCT_H
#define STRUCT_H

#include "include.h"

// enum of piece types on squares
typedef enum {BLACK_KING = -2, BLACK_PIECE, EMPTY, WHITE_PIECE, WHITE_KING, LOCK, GHOST} SQUARE;

// enum for direction of player
typedef enum {NORD, SUD} DIRECTION ;

// enum for player color for negaMax algorithm
typedef enum {WHITE=-1, BLACK=1} COLOR ;

// struct for move modelisation for negaMax algorithm
typedef struct{
    int x ;
    int y ;
    int xDest ;
    int yDest ;
} MOVE ;

// struct with move and his value for negaMax algorithm
typedef struct {
    MOVE m ;
    int value ;
} MOVEVALUE ;

#endif // STRUCT_H
