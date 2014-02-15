#ifndef MAIN_H
#define MAIN_H

#define MIN_LENGTH 4
#define MIN_HEIGHT 4

// enum of piece types on squares
typedef enum {BLACK_KING = -2, BLACK_PIECE, EMPTY, WHITE_PIECE, WHITE_KING, LOCK} SQUARE;

// enum for direction of player
typedef enum {NORD, SUD} DIRECTION ;

// parameters scan menu for custom game
void customization(int & height, int & length, int & nbLinePiece1, int & nbLinePiece2) ;

// main for game developping
int mainGame() ;

// main for graphic developping
int mainGraphic() ;

#endif