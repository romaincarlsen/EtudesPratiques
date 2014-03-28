#ifndef GAME_H
#define GAME_H

#define MIN_SIZE 4

#include "include.h"
#include "Tools.h"
#include "Checkerboard.h"
#include "Player.h"
#include "PlayerCP.h"
#include "PlayerManual.h"

class Game
{

private:
    Player* P1 ;
    Player* P2 ;
    Checkerboard* board ;
    QString in ;

    int winner ;
    int size ;
    int nbLinePiece1 ;
    int nbLinePiece2 ;
    void init() ;
    //launch the game
    void launch();
    // print game
    void print() ;

    QString input() ;


public:
    void (*nextEvent)(Game*) ;
    // create game with dimension parameters
    Game();
    ~Game();
    void start() ;

    void read(QLineEdit* txt) ;
    void modeDev() ;
    void modeGame() ;
    void sizeInit() ;
    void nbPieceP1() ;
    void nbPieceP2() ;
    void selectPieceP1() ;
    void selectPieceP2() ;
    void selectDestP1() ;
    void selectDestP2() ;
};

void modeDevEvent(Game*) ;
void modeGameEvent(Game*) ;
void sizeInitEvent(Game*) ;
void nbPieceP1Event(Game*) ;
void nbPieceP2Event(Game*) ;
void selectPieceP1Event(Game*) ;
void selectPieceP2Event(Game*) ;
void selectDestP1Event(Game*) ;
void selectDestP2Event(Game*) ;

#endif

