#ifndef GAME_H
#define GAME_H

#define MIN_SIZE 4

#include "include.h"
#include "Tools.h"
#include "Checkerboard.h"
#include "Player.h"

class Game
{

private:
    Player* P1 ;
    Player* P2 ;
    Checkerboard* board ;

    STATE state ;

    QString txt ;

    int winner ;
    int size ;
    int nbLinePiece1 ;
    int nbLinePiece2 ;

public:

    // create game with dimension parameters
    Game(int size, int nbLineP1, int nbLineP2, int p1 = -1, int p2 =-1) ;
    ~Game();

    Checkerboard* getBoard() ;

    bool execMove(int x, int y, int xDest, int yDest) ;

    bool isCPTurn() ;

    bool isFinish() ;

    MOVE negaMax() ;

    bool isWhiteState(STATE state) ;
    bool isBlackState(STATE state) ;

    STATE select(Player* player, int x, int y) ;
    STATE dest(Player* player,  Player* opponent, int xDest, int yDest) ;

    // print game
    QString toString() ;

    void paint(QGridLayout* board_gl) ;

    int costFunction(Checkerboard* board, Player* player, COLOR color) ;

    std::vector<MOVE> findMoveOnBoard(Checkerboard* board, COLOR color, Player* player) ;

    int negaMax(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best) ;

    Player* playerTurn() ;

};

#endif

