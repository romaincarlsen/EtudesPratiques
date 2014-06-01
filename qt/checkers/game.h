#ifndef GAME_H
#define GAME_H
#define MIN_SIZE 4

#include "include.h"
#include "Tools.h"
#include "Checkerboard.h"
#include "Player.h"

// struct with move and his value for negaMax algorithm
typedef struct {
    MOVE move ;
    Checkerboard board ;
    bool valued ;
    int value ;
    int xSelect ;
    int ySelect ;
} CHILD ;

class Game
{
private:
    // Player 1 = white player
    Player* P1 ;
    // Player 2 =  black player
    Player* P2 ;
    // the checkerboard of the game
    Checkerboard board ;
    // the current state of the game (white to select, ...)
    STATE state ;
    // texte affiché dans les instructions (Veuillez sélectionner une pièce, ...)
    QString txt ;
    // the numero of the winner
    int winner ;
    // the board size of the game
    int size ;
    // the number of line pieces for white player
    int nbLinePiece1 ;
    // the number of line pieces for black player
    int nbLinePiece2 ;
    // the url of the reporting file saving
    QString url_reporting;
    // values to write in the reporting file
    std::vector<string> reporting ;
    // time corresponding of begin of the last/current IA algorithm launching
    timeval time_IA_begin ;
    bool _stop;
public:
    // with alphabeta parameter
    bool with_alphabeta;
    // with thread parameter
    bool with_thread;
    // with reporting parameter
    bool with_reporting;
    // create game with dimension parameters
    Game(int size, int nbLineP1, int nbLineP2, int p1 = -1,int costFunction1=1, int p2 =-1, int costFunction2=1, bool alphabeta=false, bool thread=false, bool reporting=false) ;
    ~Game();
    Checkerboard getBoard() ;
    int getSize();
    Player* getP1() ;
    Player* getP2() ;
    // execute the move from x y to xDest yDest on the game board
    // return true if there is a winner at the end of the turn
    bool execMove(int x, int y, int xDest, int yDest) ;
    // return true if the player who have to play is a computer
    bool isCPTurn() ;
    // return true if the game is finish
    bool isFinish() ;
    // return true if the game if finish on the board in parameter
    // if there is a winner or if player in parameter can't move
    bool isFinishOnBoard(const Checkerboard & board, Player *player) ;
    // return true if the player in parameter can't move
    bool isEqualityOnBoard(const Checkerboard & board, Player *player) ;
    // return true if the current game state indicate it's to white player to play
    bool isWhiteState(STATE state) ;
    // return true if the current game state indicate it's to black player to play
    bool isBlackState(STATE state) ;
    // return true if the current game state indicate a player have to select a piece
    bool isStateSelect();
    // select the piece on x y square for player in parameter
    // return the new game state after the action
    STATE select(Player* player, int x, int y) ;
    // select the destination square xdest yDest for the player in parameter
    // execute the move if destination square selected is valid
    // return the new game state after the action
    STATE dest(Player* player,  Player* opponent, int xDest, int yDest) ;
    //Méthode qui déselectionne le pion sélectionné.
    bool deselect();
    // print game
    QString toString() ;
    // cost functions
    int costFunction(const Checkerboard & board, COLOR color) ;
    int costFunction1(const Checkerboard & board, COLOR color) ;
    int costFunction2(const Checkerboard & board, COLOR color) ;
    int costFunction3(const Checkerboard & board, COLOR color) ;
    int costFunction4(const Checkerboard & board, COLOR color) ;
    int costFunction5(const Checkerboard & board, COLOR color);
    // return all the struct MOVE possible for the player on the board parameters
    std::vector<MOVE> findMoveOnBoard(const Checkerboard & board, COLOR color, Player* player) ;
    // return all the struct MOVE possible for the player on the board parameters from xSelect ySelect square
    std::vector<MOVE> findMoveOnBoardFrom(const Checkerboard & board, COLOR color, Player* player, int x, int y) ;
    // return all the struct CHILD possible for the player on the board parameters from xSelect ySelect square
    std::vector<CHILD> findChild(const Checkerboard & board, COLOR color, Player* player, int xSelect, int ySelect) ;
    // return the best child value in the child treated et the struct MOVES corresponding
    int findBestChild(std::vector<CHILD> child, std::vector<MOVE> & best, int nb_child_treated) ;
    // init and launch the negamax algorithm
    // launch with threads if the parameter is true
    MOVE negaMax(bool with_thread_param) ;
    // launch recursively the negamax algorithm without threads
    int negaMaxClassic(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int xSelect, int ySelect) ;
    // launch recursively the negamax algorithm with threads
    int negaMaxThread(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int xSelect, int ySelect) ;
    // init and launch the alphabeta algorithm
    // launch with threads if the parameter is true
    MOVE alphaBeta(bool with_thread_param) ;
    // launch recursively the alphabeta algorithm without threads
    int alphaBetaClassic(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect);
    // launch recursively the alphabeta algorithm with threads
    int alphaBetaThread(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect);
    // return the player who have to play
    Player* playerTurn() ;
    // init the reporting creation
    void init_reporting() ;
    // add informations in parameters corresponding to a node of algorithm tree in the reporting to write
    void add_node_reporting(const Checkerboard & board, int value, double time, int nb_child, int nb_child_treated) ;
    // write reporting in the reporting file
    void save_reporting() ;
    //Gestion de l'arret en cours de calcul de l'IA lors de la fermeture de la fenetre
    void stop();
};
#else
class Game ;
#endif
