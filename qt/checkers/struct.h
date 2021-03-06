#ifndef STRUCT_H
#define STRUCT_H

#include "include.h"
#include "labelcase.h"

// enum of piece types on squares
typedef enum {BLACK_KING = -2, BLACK_PIECE, EMPTY, WHITE_PIECE, WHITE_KING, LOCK, GHOST, UNDEFINED} SQUARE;

// enum for direction of player
typedef enum {NORD, SUD} DIRECTION ;

// enum for player color for negaMax algorithm
typedef enum {WHITE=-1, BLACK=1} COLOR ;

// enum for state machine corresponding with game loop
typedef enum {WHITE_SELECT, WHITE_DEST, BLACK_SELECT, BLACK_DEST, END} STATE ;

// structure of the square of the checkerboards
typedef struct {
    SQUARE square ;
    int x ;
    int y ;
} QSQUARE ;

// struct for move modelisation for negaMax algorithm
typedef struct{
    int x ;
    int y ;
    int xDest ;
    int yDest ;
} MOVE ;

//Damier : contient les informations du jeu (plateau, placement des piéces)
typedef std::vector<std::vector<QSQUARE> > Damier;
//Board : contient les images à afficher
typedef std::vector<std::vector<LabelCase*> > Board;
#else

#endif // STRUCT_H
