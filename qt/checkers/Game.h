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

    STATE state ;

    QString in ;

    QString txt ;

    int winner ;
    int size ;
    int nbLinePiece1 ;
    int nbLinePiece2 ;

    QString input() ;


public:

    // create game with dimension parameters
    Game(int size, int nbLineP1, int nbLineP2) ;
    ~Game();

    Checkerboard* getBoard() ;

    void clickOnBoard(QLineEdit* ok_tb) ;
    void clickOnBoard(int x, int y);

    STATE select(Player* player, int x, int y) ;
    STATE dest(Player* player,  Player* opponent, int xDest, int yDest) ;

    // print game
    QString toString() ;

    void paint(QGridLayout* board_gl) ;

};

#endif

