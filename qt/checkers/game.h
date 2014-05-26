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

    QString url_reporting;
    std::vector<string> reporting ;

    //float time_IA_begin ;
    //time_t time_IA_begin ;
    timeval time_IA_begin ;

public:

    bool with_alphabeta;
    bool with_thread;

    // create game with dimension parameters
    Game(int size, int nbLineP1, int nbLineP2, int p1 = -1,int costFunction1=1, int p2 =-1, int costFunction2=1, bool alphabeta=false, bool thread=false) ;
    ~Game();

    Checkerboard* getBoard() ;
    int getSize();
    Player* getP1() ;
    Player* getP2() ;

    bool execMove(int x, int y, int xDest, int yDest) ;

    bool isCPTurn() ;

    bool isFinish() ;

    bool isFinishOnBoard(Checkerboard* board, Player *player) ;
    bool isEqualityOnBoard(Checkerboard* board, Player *player) ;

    bool isWhiteState(STATE state) ;
    bool isBlackState(STATE state) ;
    bool isStateSelect();

    STATE select(Player* player, int x, int y) ;
    STATE dest(Player* player,  Player* opponent, int xDest, int yDest) ;

    //Méthode qui déselectionne le pion sélectionné.
    bool deselect();

    // print game
    QString toString() ;

    int costFunction(Checkerboard* board, Player* player, COLOR color) ;

    int costFunction1(Checkerboard* board, Player* player, COLOR color) ;

    int costFunction2(Checkerboard* board, Player* player, COLOR color) ;

    int costFunction3(Checkerboard* board, Player* player, COLOR color) ;

    int costFunction4(Checkerboard* board, Player* player, COLOR color) ;

    std::vector<MOVE> findMoveOnBoard(Checkerboard* board, COLOR color, Player* player) ;

    std::vector<MOVE> findMoveOnBoardFrom(Checkerboard* board, COLOR color, Player* player, int xSelect, int ySelect) ;

    std::vector<CHILD> findChild(Checkerboard* board, COLOR color, Player* player, int xSelect, int ySelect) ;
    int findBestChild(std::vector<CHILD> child, std::vector<MOVE> & best) ;

    MOVE negaMax(bool with_thread_param) ;
    int negaMaxClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int xSelect, int ySelect) ;
    int negaMaxThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int xSelect, int ySelect) ;

    MOVE alphaBeta(bool with_thread_param) ;
    int alphaBetaClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect);
    int alphaBetaThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect);

    Player* playerTurn() ;

    void init_reporting() ;
    void add_node_reporting(Checkerboard* board, int value, double time, int nb_child, int nb_child_treated) ;
    void save_reporting() ;
    INFO getInfo(Checkerboard* board, Player* player, Player* opponent) ;
    bool apply(Checkerboard* board) ;

};

#endif

