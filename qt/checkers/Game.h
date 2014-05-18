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

    QString url_reporting = "coup.txt" ;
    std::vector<string> reporting ;

public:

    bool with_alphabeta = false ;
    bool with_thread = false ;
    int nb_thread = 4 ;

    // create game with dimension parameters
    Game(int size, int nbLineP1, int nbLineP2, int p1 = -1, int p2 =-1) ;
    ~Game();

    Checkerboard* getBoard() ;

    bool execMove(int x, int y, int xDest, int yDest) ;

    bool isCPTurn() ;

    bool isFinish() ;

    bool isFinishOnBoard(Checkerboard* board) ;
    bool isEqualityOnBoard(Checkerboard* board) ;

    bool isWhiteState(STATE state) ;
    bool isBlackState(STATE state) ;

    STATE select(Player* player, int x, int y) ;
    STATE dest(Player* player,  Player* opponent, int xDest, int yDest) ;

    //Méthode qui déselectionne le pion sélectionné.
    void deselect();

    // print game
    QString toString() ;

    void paint(QGridLayout* board_gl) ;

    int costFunction(Checkerboard* board, Player* player, COLOR color) ;

    std::vector<MOVE> findMoveOnBoard(Checkerboard* board, COLOR color, Player* player) ;

    std::vector<CHILD> findChild(Checkerboard* board, COLOR color, Player* player) ;
    int findBestChild(std::vector<CHILD> child, std::vector<MOVE> & best) ;

    MOVE negaMax(bool with_thread_param) ;
    int negaMaxClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best) ;
    int negaMaxThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best) ;

    MOVE alphaBeta(bool with_thread_param) ;
    int alphaBetaClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec);
    int alphaBetaThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec);

    Player* playerTurn() ;

    void init_reporting() ;
    void add_node_reporting(Checkerboard* board, int value, int nb_child, int nb_child_treated) ;
    void save_reporting() ;
};

#endif

