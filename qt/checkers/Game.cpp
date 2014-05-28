#include "game.h"

Game::Game(int size, int nbLineP1, int nbLineP2, int p1,int costFunction1, int p2, int costFunction2, bool alphabeta, bool thread, bool reporting){
    this->size = size ;
    this->nbLinePiece1 = nbLineP1 ;
    this->nbLinePiece2 = nbLineP2 ;
    winner = 0 ;
    // init board
    board = new Checkerboard(size) ;
    // init players
    P1 = new Player(nbLinePiece1, board, NORD, p1) ;
    P2 = new Player(nbLinePiece2, board, SUD, p2) ;
    P1->costFunction=costFunction1;
    P2->costFunction=costFunction2;
    // current state of game loop in state machine

    txt = P1->toString() + "\n\n" ;
    // delete pieces which have been killed during last turn
    board->ghostBuster() ;
    //Player 1 turn

    // piece selection
    txt += "select (ex : A1) :   " ;

    state = WHITE_SELECT ;

    url_reporting = "coup.txt" ;
    with_alphabeta = alphabeta ;
    with_thread = thread ;
    with_reporting = reporting;

    if (with_reporting) {
        qDebug() << with_reporting ;

    }

}


Game::~Game() {
    delete board ;
    delete P1 ;
    delete P2 ;
}

Checkerboard* Game::getBoard() {
    return board ;
}

int Game::getSize() {
    return size ;
}
Player* Game::getP1(){
    return P1;
}

Player* Game::getP2(){
    return P2;
}

bool Game::execMove(int x, int y, int xDest, int yDest){

    if(x!=-1 && y!=-1) {
        switch (state) {
        case WHITE_SELECT :     state = select(P1, x, y) ;
            return true ;
        case BLACK_SELECT :     state = select(P2, x, y) ;
            return true ;
        }
    }
    if(xDest!=-1 && yDest!=-1) {
        switch (state) {
        case WHITE_DEST :       state = dest(P1, P2, xDest, yDest) ;
            return true ;

        case BLACK_DEST :       state = dest(P2, P1, xDest, yDest) ;
            return true ;
        }
    }
    return false ;
}

bool Game::isCPTurn() {
    return (isWhiteState(state) && P1->isCP()) || (isBlackState(state) && P2->isCP()) ;
}

bool Game::isFinish() {
    return state == END ;
}


bool Game::isFinishOnBoard(Checkerboard* board, Player * player) {
    return board->isWin() || isEqualityOnBoard(board, player) ;
}

bool Game::isEqualityOnBoard(Checkerboard* board, Player* player) {
    if (player->isWhite()){
        return (findMoveOnBoard(board,WHITE,player).size()==0 && !(board->isWin()));
    }
    else{
        return (findMoveOnBoard(board,BLACK,player).size()==0  && !(board->isWin()));
    }
}

bool Game::isWhiteState(STATE state) {
    return state == WHITE_SELECT || state == WHITE_DEST ;
}

bool Game::isBlackState(STATE state) {
    return state == BLACK_SELECT || state == BLACK_DEST ;
}

bool Game::isStateSelect(){
    return state == WHITE_SELECT || state == BLACK_SELECT ;
}

STATE Game::select(Player* player, int x, int y) {

    if (x>=0 && x<board->getSize() && y>=0 && y<board->getSize()) {
        if (player->selectValidOnBoard(x,y, board)) {
            player->x = x ;
            player->y = y ;
            txt += "destination : (ex : A1) :   " ;
            board->select(x,y);
            return player->state_dest ;
        }
    }
    return state ;
}


STATE Game::dest(Player* player,  Player* opponent, int xDest, int yDest) {
    if (xDest>=0 && xDest<board->getSize() && yDest>=0 && yDest<board->getSize()) {
        bool canKill = player->haveKillOnBoard(board) ;
        bool valid = player->isMoveValidOnBoard(board->getSquare(player->x,player->y),player->x,player->y,xDest,yDest, board) ;
        if (valid) {
            bool wasKill = player->isKillOnBoard(board->getSquare(player->x,player->y),player->x,player->y,xDest,yDest,board) ;
            if(!(valid=!(canKill && !wasKill))) {
                txt += "\nYou have to kill !\n" ;
                txt += "select (ex : A1) :   " ;
                board->deselect();
                return player->state_select ;
            }
            else {
                if (!(valid = !wasKill || player->isTheBestKillOnBoard(board->getSquare(player->x,player->y),player->x,player->y,xDest,yDest, board, with_thread))) {
                    txt += "\nYou have to choose the best kill !\n" ;
                    txt += "select (ex : A1) :   " ;
                    if (board->moveBegined()) {
                        return state ;
                    }
                    else {
                        board->deselect() ;
                        return player->state_select ;
                    }
                }
            }
            player->xDest = xDest ;
            player->yDest = yDest ;
            bool isWin = player->moveOnBoard(player->x,player->y,player->xDest,player->yDest, board) ;
            if(isWin) {
                board->ghostBuster() ;
                txt = "winner = " + player->toString() ;
                board->deselect();
                return END ;
            }
            else {
                player->x = player->xDest ;
                player->y = player->yDest ;
                board->select(player->x, player->y) ;
                if ((wasKill && player->canKillOnBoard(board->getSquare(player->x,player->y), player->x, player->y, board))) {
                    return state ;
                }
                else {
                    if (Tools::isPiece(board->getSquare(player->x,player->y)) && player->isOnKingLineOnBoard(player->y, board))
                        board->setSquare(player->x, player->y, player->king);
                    board->ghostBuster() ;
                    bool equality = isEqualityOnBoard(board , (player==P1 ? P2 : P1)) ;
                    if (equality) {
                        txt= "equality" ;
                        board->deselect();
                        return END ;
                    }
                }

                txt = opponent->toString() + "\n\n" ;
                // delete pieces which have been killed during last turn


                // piece selection
                txt += "select (ex : A1) :   " ;
                board->deselect();
                return opponent->state_select ;
            }
        }
    }
    return state ;
}

bool Game::deselect(){
    bool enCours = false;
    bool res = false ;
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(board->getQSquare(i,j).square == GHOST) {
                enCours = true;
            }
        }
    }
    if(!enCours){
        if(isWhiteState(state)){
            state = WHITE_SELECT;
        }else state = BLACK_SELECT;
        res = board->deselect();
    }
    return res ;
}

QString Game::toString() {
    return txt ;
}


int Game::costFunction(Checkerboard* board, Player* player, COLOR color) {
    switch (playerTurn()->costFunction) {
    case 1:
        return costFunction1(board, player, color);
        break;
    case 2:
        return costFunction2(board, player, color);
        break;
    case 3:
        return costFunction3(board, player, color);
        break;
    case 4:
        return costFunction4(board, player, color);
        break;
    case 5:
        return costFunction5(board, player, color);
        break;
    default:
        return costFunction1(board, player, color);
        break;
    }
}

int Game::costFunction1(Checkerboard* board, Player* player, COLOR color) {
    player = playerTurn() ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    return ((int)color) * (nbMinePiece - nbOpponentPiece + (nbMineKing - nbOpponentKing)*3) ;
}

int Game::costFunction2(Checkerboard* board, Player* player, COLOR color) {
    player = playerTurn() ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    int value = (nbMinePiece - nbOpponentPiece)*3 + (nbMineKing - nbOpponentKing)*9 ;
    for (int x=0 ; x<board->getSize() ; x++) {
        for (int y=0 ; y<board->getSize() ; y++) {
            if (player->isMine(board->getSquare(x,y))) {
                if (x+1<board->getSize() && y+1<board->getSize())
                    value += player->isMine(board->getSquare(x+1,y+1)) ;
                if (x-1>=0 && y+1<board->getSize())
                    value += player->isMine(board->getSquare(x-1,y+1)) ;
                if (x-1>=0 && y-1>=0)
                    value += player->isMine(board->getSquare(x-1,y-1)) ;
                if (x+1<board->getSize() && y-1>=0)
                    value += player->isMine(board->getSquare(x+1,y-1)) ;
            }
        }
    }
    return ((int)color) * value ;
}

int Game::costFunction3(Checkerboard* board, Player* player, COLOR color) {
    player = playerTurn() ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    int value = (nbMinePiece - nbOpponentPiece)*3 + (nbMineKing - nbOpponentKing)*9 ;
    for (int x=0 ; x<board->getSize() ; x++) {
        for (int y=0 ; y<board->getSize() ; y++) {
            if (player->isMine(board->getSquare(x,y))) {
                value += (1/board->getSize()) * (board->getSize()/2)-max(abs(x-(board->getSize()/2)),abs(y-(board->getSize()/2)));
            }
            if (player->isOpponent(board->getSquare(x,y))) {
                value -= (1/board->getSize()) * min(abs(x-(board->getSize()/2)),abs(y-(board->getSize()/2)));
            }
        }
    }
    return ((int)color) * value ;
}

int Game::costFunction4(Checkerboard* board, Player* player, COLOR color) {
    return 0 ;
}

int Game::costFunction5(Checkerboard* board, Player* player, COLOR color) {
    return (rand()%201 - 100) ;
}

std::vector<MOVE> Game::findMoveOnBoard(Checkerboard* board, COLOR color, Player* player) {
    std::vector<MOVE> m ;
    m.resize(0);
    for (int x=0 ; x<board->getSize() ; x++) {
        for (int y=0 ; y<board->getSize() ; y++) {
            if (Tools::isWhite(board->getSquare(x,y)) && color==WHITE || Tools::isBlack(board->getSquare(x,y)) && color==BLACK) {
                if (player->selectValidOnBoard(x,y, board)) {
                    for (int xDest=0 ; xDest<board->getSize() ; xDest++) {
                        for (int yDest=0 ; yDest<board->getSize() ; yDest++) {
                            bool canKill = player->haveKillOnBoard(board) ;
                            if (player->isMoveValidOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board)) {
                                bool wasKill = player->isKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest,board) ;
                                if (!(canKill && !wasKill)) {
                                    if (!wasKill || player->isTheBestKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board, with_thread)){
                                        MOVE move ;
                                        move.x = x ;
                                        move.y = y ;
                                        move.xDest = xDest ;
                                        move.yDest = yDest ;
                                        m.push_back(move) ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return m ;
}

std::vector<MOVE> Game::findMoveOnBoardFrom(Checkerboard* board, COLOR color, Player* player, int xSelect, int ySelect) {
    std::vector<MOVE> m ;
    m.resize(0);
    int x = xSelect ;
    int y = ySelect ;

    if (Tools::isWhite(board->getSquare(x,y)) && color==WHITE || Tools::isBlack(board->getSquare(x,y)) && color==BLACK) {
        if (player->selectValidOnBoard(x,y, board)) {
            for (int xDest=0 ; xDest<board->getSize() ; xDest++) {
                for (int yDest=0 ; yDest<board->getSize() ; yDest++) {
                    bool canKill = player->haveKillOnBoard(board) ;
                    if (player->isMoveValidOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board)) {
                        bool wasKill = player->isKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest,board) ;
                        if (!(canKill && !wasKill)) {
                            if (!wasKill || player->isTheBestKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board, with_thread)){

                                MOVE move ;
                                move.x = x ;
                                move.y = y ;
                                move.xDest = xDest ;
                                move.yDest = yDest ;
                                m.push_back(move) ;
                            }
                        }
                    }
                }
            }
        }
    }
    return m ;


}

std::vector<CHILD> Game::findChild(Checkerboard* board, COLOR color, Player* player, int xSelect, int ySelect) {
    std::vector<CHILD> child ;
    child.resize(0) ;
    std::vector<MOVE> move ;
    if (xSelect!=-1 && ySelect!=-1)
        move = findMoveOnBoardFrom(board,color, player,xSelect,ySelect) ;
    else
        move = findMoveOnBoard(board,color, player) ;
    //child.resize(move.size());
    for (int i = 0 ; i<move.size() ; i++) {
        CHILD test ;
        test.move = move[i] ;
        test.board = new Checkerboard(board) ;
        test.valued = false ;
        test.xSelect = -1 ;
        test.ySelect = -1 ;

        Checkerboard * tmp_board = (Checkerboard*)(test.board) ;
        int x = test.move.x ;
        int y = test.move.y ;
        int xDest = test.move.xDest ;
        int yDest = test.move.yDest ;
        bool loop = true ;

        bool wasKill = player->isKillOnBoard(tmp_board->getSquare(x,y),x,y,xDest,yDest,tmp_board) ;
        bool isWin = player->moveOnBoard(x,y,xDest,yDest,tmp_board) ;
        if(isWin) {
            tmp_board->ghostBuster() ;
        }
        else {
            if ((wasKill && player->canKillOnBoard(tmp_board->getSquare(xDest,yDest), xDest, yDest, tmp_board))) {
                test.xSelect = xDest ;
                test.ySelect = yDest ;
            }
            else {
                if (Tools::isPiece(tmp_board->getSquare(xDest,yDest)) && player->isOnKingLineOnBoard(yDest, tmp_board))
                    tmp_board->setSquare(xDest, yDest, player->king);
                tmp_board->ghostBuster() ;
            }
        }
        child.push_back(test);
    }
    return child ;
}

int Game::findBestChild(std::vector<CHILD> child, std::vector<MOVE> & best, int nb_child_treated) {
    int value ;
    for (int i = 0 ; i<nb_child_treated ; i++) {
        //if (depth == playerTurn()->getLevel()) {
        if (i==0 || child[i].value >= value) {
            if (i==0 || child[i].value > value) {
                value = child[i].value ;
                best.clear();
            }
            best.push_back(child[i].move) ;
        }
        //}
    }
    return value ;
}

MOVE Game::negaMax(bool with_thread_param) {
    std::vector<MOVE> m ;
    m.resize(0);
    init_reporting();
    //time_IA_begin = omp_get_wtime();
    gettimeofday(&time_IA_begin , NULL) ;

    int xSelect = -1 ;
    int ySelect = -1 ;
    if (board->selection.select) {
        xSelect = board->selection.x ;
        ySelect = board->selection.y ;
    }

    int value ;
    if (isWhiteState(state) && P1->isCP()) {
        if (with_thread_param) {
#pragma omp single
            value = ((int)WHITE) * negaMaxThread(board, P1->getLevel(), WHITE, P1, P2, m, xSelect, ySelect) ;
        }
        else
            value = ((int)WHITE) * negaMaxClassic(board, P1->getLevel(), WHITE, P1, P2, m,xSelect, ySelect) ;
    }

    if (isBlackState(state) && P2->isCP()) {
        if (with_thread_param) {
#pragma omp single
            value = ((int)BLACK) * negaMaxThread(board, P2->getLevel(), BLACK, P1, P2, m, xSelect, ySelect) ;
        }
        else
            value = ((int)BLACK) * negaMaxClassic(board, P2->getLevel(), BLACK, P1, P2, m, xSelect, ySelect) ;
    }
    if(with_reporting) {save_reporting();}


    if (m.empty()) {
        MOVE error ;
        error.x = error.y = error.xDest = error.yDest = -1 ;
        return error ;
    }
    return m[rand()%m.size()];
}

//function negamax(node, depth, color)
//if depth = 0 or node is a terminal node
//    return color * the heuristic value of node
//bestValue := -infini
//foreach child of node
//    val := -negamax(child, depth - 1, -color)
//    bestValue := max( bestValue, val )
//return bestValue
//
//Initial call for Player A's root node
//rootNodeValue := negamax( rootNode, depth, 1)
//
//Initial call for Player B's root node
//rootNodeValue := -negamax( rootNode, depth, -1)
int Game::negaMaxClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int xSelect, int ySelect) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;
    int value ;
    std::vector<CHILD> child ;
    child.resize(0) ;
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color) ;

        //add_node_reporting(board,value,omp_get_wtime()-time_IA_begin,child.size(),child.size()) ;

        if(with_reporting) {
            timeval end ;
            gettimeofday(&end , NULL) ;
            add_node_reporting(board,-value,Tools::timediff(time_IA_begin,end),child.size(),child.size()) ;
        }
        return value ;
    }
    child = findChild(board,color, player, xSelect, ySelect) ;

    for (int i = 0 ; i<child.size() ; i++) {
        QCoreApplication::processEvents();
        if (omp_get_num_threads()>1)
            qDebug() << "nb threads = " << omp_get_num_threads() ;
        child[i].value = - negaMaxClassic((Checkerboard*)(child[i].board), depth - 1, (COLOR)(-(int)color),P1, P2, best, child[i].xSelect, child[i].ySelect) ;
        delete (Checkerboard*)(child[i].board) ;
    }
    value = findBestChild(child,best,child.size()) ;

    if(with_reporting) {
        timeval end ;
        gettimeofday(&end , NULL) ;
        add_node_reporting(board,-value,Tools::timediff(time_IA_begin,end),child.size(),child.size()) ;
    }

    return value ;
}

/*int core;
struct timespec start;
struct timespec stop;
double delay;
double *test;
double test0;
test = new double [4];
omp_set_num_threads(4);
clock_gettime(CLOCK_MONOTONIC, &start);
test0 = omp_get_wtime();
#pragma omp parallel for
for ( core = 0 ; core < 4 ; core++)
{
   // ptModule[core].Main();
    test[core] = omp_get_wtime();
}

// Setting the Stop timestamp for compute time
clock_gettime(CLOCK_MONOTONIC, &stop);

// Compute time delay
for ( core = 0 ; core < 4 ; core++)
    qDebug() << "core " << core << " : " << 1000000*(test[core]-test0);
delay = ( stop.tv_sec - start.tv_sec ) + (double) ( stop.tv_nsec - start.tv_nsec ) / 1000000000;
qDebug() << "total : " << 1000000*delay ;*/
int Game::negaMaxThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best , int xSelect, int ySelect) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;
    int value ;
    std::vector<CHILD> child ;
    child.resize(0) ;
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color) ;

        return value ;
    }
    child = findChild(board,color, player, xSelect, ySelect) ;

    //#pragma parallel section

#pragma omp parallel
    {
        for (int i = 0 ; i<(int)child.size() ; i++) {
            QCoreApplication::processEvents();
            /*#pragma omp single
            {*/
            int test ;
#pragma omp task
            {
                if (omp_get_num_threads()>1)
                    qDebug() << "nb threads = " << omp_get_num_threads() ;
                test = - negaMaxThread((Checkerboard*)(child[i].board), depth - 1, (COLOR)(-(int)color),P1, P2, best, child[i].xSelect, child[i].ySelect) ;
            }
#pragma omp taskwait
            child[i].value = test ;
            //delete (Checkerboard*)(child[i].board) ;
            //}
        }
    }
    value = findBestChild(child,best,child.size()) ;

    return value ;
}

MOVE Game::alphaBeta(bool with_thread_param) {
    std::vector<MOVE> m ;
    m.resize(0);
    init_reporting() ;

    gettimeofday(&time_IA_begin , NULL) ;

    int xSelect = -1 ;
    int ySelect = -1 ;
    if (board->selection.select) {
        xSelect = board->selection.x ;
        ySelect = board->selection.y ;
    }

    int value ;
    if (isWhiteState(state) && P1->isCP()) {
        if (with_thread_param) {
#pragma parallel section
            value = ((int)WHITE) * alphaBetaThread(board, P1->getLevel(), WHITE, P1, P2, m,-value,false, xSelect, ySelect) ;
        }
        else
            value = ((int)WHITE) * alphaBetaClassic(board, P1->getLevel(), WHITE, P1, P2, m,-value,false, xSelect, ySelect) ;
    }
    if (isBlackState(state) && P2->isCP()) {
        if (with_thread_param) {
            value = ((int)BLACK) * alphaBetaThread(board, P2->getLevel(), BLACK, P1, P2, m,-value,false, xSelect, ySelect) ;
        }
        else
            value = ((int)BLACK) * alphaBetaClassic(board, P2->getLevel(), BLACK, P1, P2, m,-value,false, xSelect, ySelect) ;
    }
    if(with_reporting)save_reporting();
    if (m.empty()) {
        MOVE error ;
        error.x = error.y = error.xDest = error.yDest = -1 ;
        return error ;
    }
    return m[rand()%m.size()];
}

int Game::alphaBetaClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec , int xSelect, int ySelect) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;
    int value ;
    std::vector<CHILD> child ;
    child.resize(0) ;
    int nb_child_treated = 0 ;
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color);

        if(with_reporting) {
            timeval end ;
            gettimeofday(&end , NULL) ;
            add_node_reporting(board,-value,Tools::timediff(time_IA_begin,end),child.size(),nb_child_treated) ;
        }
        return value ;
    }
    child = findChild(board,color, player, xSelect, ySelect) ;
    nb_child_treated = child.size() ;

    bool value_init = false ;
    for (int i = 0 ; i<nb_child_treated ; i++) {

        QCoreApplication::processEvents();
        if (i!=0 && ismaxprec && value>maxprec && nb_child_treated==child.size()) {
            nb_child_treated = i ;
        }
        else {
            child[i].value = -alphaBetaClassic((Checkerboard*)(child[i].board), depth - 1, (COLOR)(-(int)color),P1, P2, best, -value, i!=0, child[i].xSelect, child[i].ySelect) ;
            if (!value_init) {
                value = child[i].value ;
                value_init = true ;
            }
            else {
                if (value<child[i].value)
                    value = child[i].value ;
            }
            delete (Checkerboard*)(child[i].board) ;

        }

    }
    value = findBestChild(child,best,nb_child_treated) ;

    if(with_reporting) {
        timeval end ;
        gettimeofday(&end , NULL) ;
        add_node_reporting(board,-value,Tools::timediff(time_IA_begin,end),child.size(),nb_child_treated) ;
    }

    return value ;
}

int Game::alphaBetaThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;
    int value ;
    std::vector<CHILD> child ;
    child.resize(0) ;
    int nb_child_treated = 0 ;
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color);
        return value ;
    }
    child = findChild(board,color, player, xSelect, ySelect) ;
    nb_child_treated = child.size() ;

    bool value_init = false ;
    //#pragma omp single
#pragma omp parallel
    {
        for (int i = 0 ; i<nb_child_treated ; i++) {
            QCoreApplication::processEvents();
            if (i!=0 && ismaxprec && value>maxprec && nb_child_treated==child.size()) {
                nb_child_treated = i ;
            }
            else {
                int test ;
#pragma omp task
                {
                    if (omp_get_num_threads()>1)
                        qDebug() << "nb threads = " << omp_get_num_threads() ;

                    test = -alphaBetaThread((Checkerboard*)(child[i].board), depth - 1, (COLOR)(-(int)color),P1, P2, best, -value, i!=0, child[i].xSelect, child[i].ySelect) ;

#pragma omp taskwait
                    child[i].value = test ;

                    if (!value_init) {
                        value = child[i].value ;
                        value_init = true ;
                    }
                    else {
                        if (value<child[i].value)
                            value = child[i].value ;
                    }

                    //delete (Checkerboard*)(child[i].board) ;
                }
            }
        }
    }
    value = findBestChild(child,best,nb_child_treated) ;
    return value ;
}

Player* Game::playerTurn() {
    return (state == WHITE_SELECT || state == WHITE_DEST ? P1 : P2) ;
}

void Game::init_reporting() {
    reporting.resize(0);
}

void Game::add_node_reporting(Checkerboard* board, int value, double time, int nb_child, int nb_child_treated) {

    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << nb_child_treated) )->str() ) ;
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << nb_child) )->str() ) ;
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << (long long int)time) )->str() ) ;
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << value) )->str() ) ;
    reporting.push_back(board->toString() ) ;
}

void Game:: save_reporting() {
    std::reverse(reporting.begin(),reporting.end());
    QFile fichier(this->url_reporting);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    flux<<board->getSize();
    flux<<";";
    qDebug() << "size reporting = " << reporting.size() ;
    for (int i=0; i<reporting.size();i++){
        QString res =QString::fromStdString(reporting[i]);
        flux<<res;
        flux<<";";
    }
    fichier.close();
}

//Gestion de l'arret en cours de calcul de l'IA lors de la fermeture de la fenetre
void Game::stop(){
    _stop = false;
}
