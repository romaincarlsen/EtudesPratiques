#include "game.h"

Game::Game(int size, int nbLineP1, int nbLineP2, int p1, int p2) {
    this->size = size ;
    this->nbLinePiece1 = nbLineP1 ;
    this->nbLinePiece2 = nbLineP2 ;
    winner = 0 ;
    // init board
    board = new Checkerboard(size) ;
    // init players
    P1 = new Player(nbLinePiece1, board, NORD, p1) ;
    P2 = new Player(nbLinePiece2, board, SUD, p2) ;
    // current state of game loop in state machine

    txt = P1->toString() + "\n\n" ;
    // delete pieces which have been killed during last turn
    board->ghostBuster() ;
    //Player 1 turn

    // piece selection
    txt += "select (ex : A1) :   " ;

    state = WHITE_SELECT ;
}


Game::~Game() {
    delete board ;
    delete P1 ;
    delete P2 ;
}

Checkerboard* Game::getBoard() {
    return board ;
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

MOVE Game::negaMax(bool with_thread_param) {

    std::vector<MOVE> m ;
    m.resize(0);
    QFile fichier("coup.txt");
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);

    std::vector<string> text ;
    text.resize(0);


    int value ;
    if (isWhiteState(state) && P1->isCP()) {
        if (with_thread_param) {
            #pragma parallel section
            value = ((int)WHITE) * negaMaxThread(board, P1->getLevel(), WHITE, P1, P2, m,text) ;
        }
        else
            value = ((int)WHITE) * negaMaxClassic(board, P1->getLevel(), WHITE, P1, P2, m,text) ;
    }
    if (isBlackState(state) && P2->isCP()) {
        if (with_thread_param) {
             #pragma parallel section
            value = ((int)BLACK) * negaMaxThread(board, P2->getLevel(), BLACK, P1, P2, m,text) ;
        }
        else
            value = ((int)BLACK) * negaMaxClassic(board, P2->getLevel(), BLACK, P1, P2, m,text) ;
    }

    text.resize(text.size()+2);
    text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
    text[text.size()-1]=board->toString();
    std::reverse(text.begin(),text.end());

    QTextStream flux(&fichier);

    flux<<board->getSize();
    flux<<";";

    for (int i=0; i<text.size();i++){
        QString res =QString::fromStdString(text[i]);
        flux<<res;
        flux<<";";
    }


    fichier.close();
    if (m.empty()) {
        MOVE error ;
        error.x = error.y = error.xDest = error.yDest = -1 ;
        return error ;
    }
    return m[rand()%m.size()];
}

MOVE Game::alphaBeta(bool with_thread_param) {

    std::vector<MOVE> m ;
    m.resize(0);
    QFile fichier("coup.txt");
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);

    std::vector<string> text ;
    text.resize(0);


    int value ;
    if (isWhiteState(state) && P1->isCP()) {
        if (with_thread_param) {
            #pragma parallel section
            value = ((int)WHITE) * alphaBetaThread(board, P1->getLevel(), WHITE, P1, P2, m,text,0,false) ;
        }
        else
            value = ((int)WHITE) * alphaBetaClassic(board, P1->getLevel(), WHITE, P1, P2, m,text,0,false) ;
    }
    if (isBlackState(state) && P2->isCP()) {
        if (with_thread_param) {
             #pragma parallel section
            value = ((int)BLACK) * alphaBetaThread(board, P2->getLevel(), BLACK, P1, P2, m,text,0,false) ;
        }
        else
            value = ((int)BLACK) * alphaBetaClassic(board, P2->getLevel(), BLACK, P1, P2, m,text,0,false) ;
    }

    text.resize(text.size()+2);
    text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
    text[text.size()-1]=board->toString();
    std::reverse(text.begin(),text.end());

    QTextStream flux(&fichier);

    flux<<board->getSize();
    flux<<";";

    for (int i=0; i<text.size();i++){
        QString res =QString::fromStdString(text[i]);
        flux<<res;
        flux<<";";
    }


    fichier.close();
    if (m.empty()) {
        MOVE error ;
        error.x = error.y = error.xDest = error.yDest = -1 ;
        return error ;
    }
    return m[rand()%m.size()];
}

bool Game::isWhiteState(STATE state) {
    return state == WHITE_SELECT || state == WHITE_DEST ;
}

bool Game::isBlackState(STATE state) {
    return state == BLACK_SELECT || state == BLACK_DEST ;
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
                if (!(valid = !wasKill || player->isTheBestKillOnBoard(board->getSquare(player->x,player->y),player->x,player->y,xDest,yDest, board))) {
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
            if(player->moveOnBoard(player->x,player->y,player->xDest,player->yDest, board)) {
                winner = (player->isWhite() ? 1 : 2);
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
                }

                txt = opponent->toString() + "\n\n" ;
                // delete pieces which have been killed during last turn
                board->ghostBuster() ;

                // piece selection
                txt += "select (ex : A1) :   " ;
                board->deselect();
                return opponent->state_select ;
            }
        }
    }
    return state ;
}

void Game::deselect(){
    if(isWhiteState(state)){
        state = WHITE_SELECT;
    }else state = BLACK_SELECT;
    board->deselect();
}

QString Game::toString() {
    return txt ;
}

void Game::paint(QGridLayout* board_gl) {
    board->paint(board_gl) ;
}


int Game::costFunction(Checkerboard* board, Player* player, COLOR color) {
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    return ((int)color) * (nbMinePiece - nbOpponentPiece + (nbMineKing - nbOpponentKing)*3) ;
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
                                    if (!wasKill || player->isTheBestKillOnBoard(board->getSquare(x,y),x,y,xDest,yDest, board)){
                                        m.resize(m.size()+1);
                                        MOVE move ;
                                        move.x = x ;
                                        move.y = y ;
                                        move.xDest = xDest ;
                                        move.yDest = yDest ;
                                        m[m.size()-1] = move ;
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
int Game::negaMaxClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, std::vector<string> &text) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;

    if (depth==0 || board->isWin()){
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        return ((int)color) * costFunction(board, player, color);
    }
    std::vector<MOVE> move = findMoveOnBoard(board,color, player) ;

    int value ;
    if (move.size()>0) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[0].x,move[0].y,move[0].xDest,move[0].yDest,child) ;


        value = -negaMaxClassic(child, depth - 1, (COLOR)(-(int)color), P1, P2, best,text) ;
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
        text[text.size()-1]=child->toString();
        if (depth == playerTurn()->getLevel()) {
            best.resize(best.size()+1) ;
            best[best.size()-1] = move[0] ;
        }
        delete child ;
    }
    int i;
    for (i = 1 ; i<move.size() ; i++) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[i].x,move[i].y,move[i].xDest,move[i].yDest,child) ;
        int value_child = - negaMaxClassic(child, depth - 1, (COLOR)(-(int)color),P1, P2, best,text) ;

        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
        text[text.size()-1]=child->toString();
        if (value_child > value) {
            value = value_child ;
            if (depth == playerTurn()->getLevel()) {
                best.clear();
                best.resize(best.size()+1) ;
                best[best.size()-1] = move[i] ;
            }
        }
        else {
            if (value_child == value) {
                if (depth == playerTurn()->getLevel()) {
                    best.resize(best.size()+1) ;
                    best[best.size()-1] = move[i] ;
                }
            }
        }
        delete child ;
    }
    text.resize(text.size()+2);
    text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << i) )->str();
    text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << move.size()) )->str();
    return value ;
}


int Game::negaMaxThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, std::vector<string> &text) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;

    if (depth==0 || board->isWin()){
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        return ((int)color) * costFunction(board, player, color);
    }
    std::vector<MOVE> move = findMoveOnBoard(board,color, player) ;

    int value ;
    if (move.size()>0) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[0].x,move[0].y,move[0].xDest,move[0].yDest,child) ;


        value = -negaMaxThread(child, depth - 1, (COLOR)(-(int)color), P1, P2, best,text) ;
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
        text[text.size()-1]=child->toString();
        if (depth == playerTurn()->getLevel()) {
            best.resize(best.size()+1) ;
            best[best.size()-1] = move[0] ;
        }
        delete child ;
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

    int nb_thread = move.size()-1 ;
    double stop_omp ;
    double *test;
    double test0;
    test = new double [nb_thread];
    omp_set_num_threads(nb_thread);

    test0 = omp_get_wtime();

    int i;
    int nb_move = move.size() ;

    #pragma omp single
    #pragma omp parallel for
    for (i = 1 ; i<nb_move ; i++) {

        //#pragma omp task

        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[i].x,move[i].y,move[i].xDest,move[i].yDest,child) ;
        int value_child = - negaMaxThread(child, depth - 1, (COLOR)(-(int)color),P1, P2, best,text) ;

        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
        text[text.size()-1]=child->toString();
        if (value_child > value) {
            value = value_child ;
            if (depth == playerTurn()->getLevel()) {
                best.clear();
                best.resize(best.size()+1) ;
                best[best.size()-1] = move[i] ;
            }
        }
        else {
            if (value_child == value) {
                if (depth == playerTurn()->getLevel()) {
                    best.resize(best.size()+1) ;
                    best[best.size()-1] = move[i] ;
                }
            }
        }
        delete child ;

        test[i-1] = omp_get_wtime();

        //#pragma omp taskwait
   }

   stop_omp = omp_get_wtime();

   // Compute time delay
   for ( int j = 0 ; j < nb_thread ; j++)
       qDebug() << "thread " << j << " : " << 1000000*(test[j]-test0);
   qDebug() << "total : " << 1000000*(stop_omp-test0) ;

    text.resize(text.size()+2);
    text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << i) )->str();
    text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << move.size()) )->str();
    return value ;
}

int Game::alphaBetaClassic(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, std::vector<string> &text, int maxprec, bool ismaxprec) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;

    if (depth==0 || board->isWin()){
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        return ((int)color) * costFunction(board, player, color);
    }
    std::vector<MOVE> move = findMoveOnBoard(board,color, player) ;

    int value ;
    if (move.size()>0) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[0].x,move[0].y,move[0].xDest,move[0].yDest,child) ;


        value = -alphaBetaClassic(child, depth - 1, (COLOR)(-(int)color), P1, P2, best,text,0,false) ;
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
        text[text.size()-1]=child->toString();
        if (depth == playerTurn()->getLevel()) {
            best.resize(best.size()+1) ;
            best[best.size()-1] = move[0] ;
        }
        delete child ;
    }

    int i;
    int nb_move = move.size() ;
    int nb_move_treated = nb_move ;

    for (i = 1 ; i<nb_move /*&& value<=maxprec*/ ; i++) {

        if (ismaxprec && value>maxprec && nb_move_treated==nb_move) {
            nb_move_treated = i ;
        }
        else {
            Checkerboard* child = new Checkerboard(board) ;
            player->moveOnBoard(move[i].x,move[i].y,move[i].xDest,move[i].yDest,child) ;

            int value_child = -alphaBetaClassic(child, depth - 1, (COLOR)(-(int)color),P1, P2, best,text, -value, true) ;
            text.resize(text.size()+2);
            text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
            text[text.size()-1]=child->toString();
            if (value_child > value) {
                value = value_child ;
                if (depth == playerTurn()->getLevel()) {
                    best.clear();
                    best.resize(best.size()+1) ;
                    best[best.size()-1] = move[i] ;
                }
            }
            else {
                if (value_child == value) {
                    if (depth == playerTurn()->getLevel()) {
                        best.resize(best.size()+1) ;
                        best[best.size()-1] = move[i] ;
                    }
                }
            }
            delete child ;
        }
    }

    text.resize(text.size()+2);
    text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << nb_move_treated) )->str();
    text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << nb_move) )->str();

    return value ;
}

int Game::alphaBetaThread(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, std::vector<string> &text, int maxprec, bool ismaxprec) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;

    if (depth==0 || board->isWin()){
        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << 0) )->str();
        return ((int)color) * costFunction(board, player, color);
    }
    std::vector<MOVE> move = findMoveOnBoard(board,color, player) ;

    int value ;
    if (move.size()>0) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[0].x,move[0].y,move[0].xDest,move[0].yDest,child) ;


        value = -alphaBetaThread(child, depth - 1, (COLOR)(-(int)color), P1, P2, best,text,0,false) ;

        text.resize(text.size()+2);
        text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
        text[text.size()-1]=child->toString();
        if (depth == playerTurn()->getLevel()) {
            best.resize(best.size()+1) ;
            best[best.size()-1] = move[0] ;
        }
        delete child ;
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

    int nb_thread = move.size()-1 ;
    double stop_omp ;
    double *test;
    double test0;
    test = new double [nb_thread];
    omp_set_num_threads(nb_thread);

    test0 = omp_get_wtime();

    int i;
    int nb_move = move.size() ;
    int nb_move_treated = nb_move ;


    #pragma omp single
    #pragma omp parallel for
    for (i = 1 ; i<nb_move /*&& value<=maxprec*/ ; i++) {

        #pragma omp task

        if (ismaxprec && value>maxprec && nb_move_treated==nb_move) {
            nb_move_treated = i ;
        }
        else {

            Checkerboard* child = new Checkerboard(board) ;
            player->moveOnBoard(move[i].x,move[i].y,move[i].xDest,move[i].yDest,child) ;

            int value_child = -alphaBetaThread(child, depth - 1, (COLOR)(-(int)color),P1, P2, best,text, -value, true) ;
            text.resize(text.size()+2);
            text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << value) )->str();
            text[text.size()-1]=child->toString();
            if (value_child > value) {
                value = value_child ;
                if (depth == playerTurn()->getLevel()) {
                    best.clear();
                    best.resize(best.size()+1) ;
                    best[best.size()-1] = move[i] ;
                }
            }
            else {
                if (value_child == value) {
                    if (depth == playerTurn()->getLevel()) {
                        best.resize(best.size()+1) ;
                        best[best.size()-1] = move[i] ;
                    }
                }
            }
            delete child ;
        }

         test[i-1] = omp_get_wtime();

         #pragma omp taskwait
    }

    stop_omp = omp_get_wtime();

    // Compute time delay
    for ( int j = 0 ; j < nb_thread ; j++)
        qDebug() << "thread " << j << " : " << 1000000*(test[j]-test0);
    qDebug() << "total : " << 1000000*(stop_omp-test0) ;

    text.resize(text.size()+2);
    text[text.size()-2]=static_cast<ostringstream*>( &(ostringstream() << nb_move_treated) )->str();
    text[text.size()-1]=static_cast<ostringstream*>( &(ostringstream() << nb_move) )->str();

    return value ;
}

Player* Game::playerTurn() {
    return (state == WHITE_SELECT || state == WHITE_DEST ? P1 : P2) ;
}
