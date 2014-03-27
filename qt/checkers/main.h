#ifndef MAIN_H
#define MAIN_H

#define MIN_SIZE 4

#include "include.h"

#include "tools.h"
#include "game.h"
#include "mainwindow.h"

QString in ;

void (*next)() ;

// parameters scan menu for custom game
void customization(int & height, int & length, int & nbLinePiece1, int & nbLinePiece2) ;

// main for game developping
int mainGame() ;

// main for graphic developping
int mainGraphic() ;

void start() ;

#endif
