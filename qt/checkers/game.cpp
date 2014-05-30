#include "game.h"

Game::Game(int size, int nbLineP1, int nbLineP2, int p1,int costFunction1, int p2, int costFunction2, bool alphabeta, bool thread, bool reporting) : size(size), nbLinePiece1(nbLineP1), nbLinePiece2(nbLineP2), winner(0), board(size){
    // create the 2 players
    // !!!! Player 1 have always to be white
    // !!!! Player 2  have always to be black
    P1 = new Player(nbLinePiece1, board, NORD, p1) ;
    P2 = new Player(nbLinePiece2, board, SUD, p2) ;
    // affecting cost function for each players
    P1->costFunction=costFunction1;
    P2->costFunction=costFunction2;
    txt = P1->toString() + "\n\n" ;
    // delete pieces which have been killed during last turn
    board.ghostBuster() ;
    txt += " Sélectionnez la piéce à déplacer." ;
    // current state of game loop in state machine
    state = WHITE_SELECT ;
    url_reporting = "coup.txt" ;
    with_alphabeta = alphabeta ;
    with_thread = thread ;
    with_reporting = reporting;
    _stop = false;
}

Game::~Game() {
    delete P1 ;
    delete P2 ;
}

Checkerboard Game::getBoard() {
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
    // select the piece if x y indicate to
    if(x!=-1 && y!=-1) {
        switch (state) {
        case WHITE_SELECT :     state = select(P1, x, y) ;
            return true ;
        case BLACK_SELECT :     state = select(P2, x, y) ;
            return true ;
        default :   break ;
        }
    }
    // select the destination square and execute the move if the xDest yDest indicate to
    if(xDest!=-1 && yDest!=-1) {
        switch (state) {
        case WHITE_DEST :       state = dest(P1, P2, xDest, yDest) ;
            return true ;

        case BLACK_DEST :       state = dest(P2, P1, xDest, yDest) ;
            return true ;
        default :   break ;
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


bool Game::isFinishOnBoard(const Checkerboard & board, Player * player) {
    return board.isWin() || isEqualityOnBoard(board, player) ;
}

bool Game::isEqualityOnBoard(const Checkerboard & board, Player* player) {
    if (player->isWhite()){
        return (findMoveOnBoard(board,WHITE,player).size()==0 && !(board.isWin()));
    }
    else{
        return (findMoveOnBoard(board,BLACK,player).size()==0  && !(board.isWin()));
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
    // verify if the x y is in the board
    if (x>=0 && x<board.getSize() && y>=0 && y<board.getSize()) {
        if (player->selectValidOnBoard(x,y, board)) {
            player->x = x ;
            player->y = y ;
            txt += " Sélectionnez la destination de votre pièce." ;
            board.select(x,y);
            return player->state_dest ;
        }
    }
    return state ;
}


STATE Game::dest(Player* player,  Player* opponent, int xDest, int yDest) {
    // verify if the x y is in the board
    if (xDest>=0 && xDest<board.getSize() && yDest>=0 && yDest<board.getSize()) {
        bool canKill = player->haveKillOnBoard(board) ;
        bool valid = player->isMoveValidOnBoard(board.getSquare(player->x,player->y),player->x,player->y,xDest,yDest, board) ;
        if (valid) {
            bool wasKill = player->isKillOnBoard(board.getSquare(player->x,player->y),player->x,player->y,xDest,yDest,board) ;
            // verify if the player doesn't choose a move without kill whereas he could kill
            if(!(valid=!(canKill && !wasKill))) {
                txt += "\nYou have to kill !\n" ;
                txt += " Sélectionnez la pièce à déplacer." ;
                board.deselect();
                return player->state_select ;
            }
            else {
                // verify if the player can't kill or if the kill chosen is the best he can do
                if (!(valid = !wasKill || player->isTheBestKillOnBoard(board.getSquare(player->x,player->y),player->x,player->y,xDest,yDest, board, with_thread))) {
                    txt += "\nYou have to choose the best kill !\n" ;
                    txt += " Sélectionnez la pièce à déplacer." ;
                    if (board.moveBegined()) {
                        return state ;
                    }
                    else {
                        board.deselect() ;
                        return player->state_select ;
                    }
                }
            }
            player->xDest = xDest ;
            player->yDest = yDest ;
            // execute the move
            // return true if the player have win after his move
            bool isWin = player->moveOnBoard(player->x,player->y,player->xDest,player->yDest, board) ;
            if(isWin) {
                board.ghostBuster() ;
                txt = "winner = " + player->toString() ;
                board.deselect();
                return END ;
            }
            else {
                player->x = player->xDest ;
                player->y = player->yDest ;
                board.select(player->x, player->y) ;
                // after have move
                // if he can have another kill with the same piece
                // keep the piece selected for he can't choose another
                if ((wasKill && player->canKillOnBoard(board.getSquare(player->x,player->y), player->x, player->y, board))) {
                    return state ;
                }
                else {
                    // tranform the piece into king if necessary
                    if (Tools::isPiece(board.getSquare(player->x,player->y)) && player->isOnKingLineOnBoard(player->y, board))
                        board.setSquare(player->x, player->y, player->king);
                    // delete pieces which have been killed during last turn
                    board.ghostBuster() ;
                    bool equality = isEqualityOnBoard(board , (player==P1 ? P2 : P1)) ;
                    if (equality) {
                        txt= "equality" ;
                        board.deselect();
                        return END ;
                    }
                }
                txt = opponent->toString() + "\n\n" ;
                txt += " Sélectionnez la pièce à déplacer." ;
                board.deselect();
                return opponent->state_select ;
            }
        }
    }
    return state ;
}

bool Game::deselect(){
    bool enCours = false;
    bool res = false ;
    // verify if there is a current move
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(board.getQSquare(i,j).square == GHOST) {
                enCours = true;
            }
        }
    }
    // if there isn't, the piece is deselected and the player have to select another
    if(!enCours){
        if(isWhiteState(state)){
            state = WHITE_SELECT;
        }else state = BLACK_SELECT;
        res = board.deselect();
    }
    return res ;
}

QString Game::toString() {
    return txt ;
}

// launch the costFunction chosen by the player whiwh it's the turn to play
int Game::costFunction(const Checkerboard & board, Player* player, COLOR color) {
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

int Game::costFunction1(const Checkerboard & board, Player* player, COLOR color) {
    player = playerTurn() ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    return ((int)color) * (nbMinePiece - nbOpponentPiece + (nbMineKing - nbOpponentKing)*3) ;
}

int Game::costFunction2(const Checkerboard & board, Player* player, COLOR color) {
    player = playerTurn() ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    int value = (nbMinePiece - nbOpponentPiece)*3 + (nbMineKing - nbOpponentKing)*9 ;
    for (int x=0 ; x<board.getSize() ; x++) {
        for (int y=0 ; y<board.getSize() ; y++) {
            if (player->isMine(board.getSquare(x,y))) {
                if (x+1<board.getSize() && y+1<board.getSize())
                    value += player->isMine(board.getSquare(x+1,y+1)) ;
                if (x-1>=0 && y+1<board.getSize())
                    value += player->isMine(board.getSquare(x-1,y+1)) ;
                if (x-1>=0 && y-1>=0)
                    value += player->isMine(board.getSquare(x-1,y-1)) ;
                if (x+1<board.getSize() && y-1>=0)
                    value += player->isMine(board.getSquare(x+1,y-1)) ;
            }
        }
    }
    return ((int)color) * value ;
}

int Game::costFunction3(const Checkerboard & board, Player* player, COLOR color) {
    player = playerTurn() ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    int value = (nbMinePiece - nbOpponentPiece)*3 + (nbMineKing - nbOpponentKing)*9 ;
    for (int x=0 ; x<board.getSize() ; x++) {
        for (int y=0 ; y<board.getSize() ; y++) {
            if (player->isMine(board.getSquare(x,y))) {
                value += (1/board.getSize()) * (board.getSize()/2)-max(abs(x-(board.getSize()/2)),abs(y-(board.getSize()/2)));
            }
            if (player->isOpponent(board.getSquare(x,y))) {
                value -= (1/board.getSize()) * min(abs(x-(board.getSize()/2)),abs(y-(board.getSize()/2)));
            }
        }
    }
    return ((int)color) * value ;
}

int Game::costFunction4(const Checkerboard & board, Player* player, COLOR color) {
    return 0 ;
}

int Game::costFunction5(const Checkerboard & board, Player* player, COLOR color) {
    return (rand()%201 - 100) ;
}

std::vector<MOVE> Game::findMoveOnBoard(const Checkerboard & board, COLOR color, Player* player) {
    std::vector<MOVE> m ;
    m.resize(0);
    // for each piece to move
    for (int x=0 ; x<board.getSize() ; x++) {
        for (int y=0 ; y<board.getSize() ; y++) {
            if ((Tools::isWhite(board.getSquare(x,y)) && color==WHITE) || (Tools::isBlack(board.getSquare(x,y)) && color==BLACK)) {
                if (player->selectValidOnBoard(x,y, board)) {
                    // for each destination corresponding
                    for (int xDest=0 ; xDest<board.getSize() ; xDest++) {
                        for (int yDest=0 ; yDest<board.getSize() ; yDest++) {
                            bool canKill = player->haveKillOnBoard(board) ;
                            if (player->isMoveValidOnBoard(board.getSquare(x,y),x,y,xDest,yDest, board)) {
                                bool wasKill = player->isKillOnBoard(board.getSquare(x,y),x,y,xDest,yDest,board) ;
                                // verify if it isn't a case where the player can kill and the move isn't a kill
                                if (!(canKill && !wasKill)) {
                                    // verify if it isn't a kill or if the kill is the best he can do
                                    if (!wasKill || player->isTheBestKillOnBoard(board.getSquare(x,y),x,y,xDest,yDest, board, with_thread)){
                                        MOVE move ;
                                        move.x = x ;
                                        move.y = y ;
                                        move.xDest = xDest ;
                                        move.yDest = yDest ;
                                        // save the move
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

std::vector<MOVE> Game::findMoveOnBoardFrom(const Checkerboard & board, COLOR color, Player* player, int xSelect, int ySelect) {
    std::vector<MOVE> m ;
    m.resize(0);
    int x = xSelect ;
    int y = ySelect ;

    if ((Tools::isWhite(board.getSquare(x,y)) && color==WHITE) || (Tools::isBlack(board.getSquare(x,y)) && color==BLACK)) {
        if (player->selectValidOnBoard(x,y, board)) {
            // for each destination corresponding from xSelect ySelect
            for (int xDest=0 ; xDest<board.getSize() ; xDest++) {
                for (int yDest=0 ; yDest<board.getSize() ; yDest++) {
                    bool canKill = player->haveKillOnBoard(board) ;
                    if (player->isMoveValidOnBoard(board.getSquare(x,y),x,y,xDest,yDest, board)) {
                        bool wasKill = player->isKillOnBoard(board.getSquare(x,y),x,y,xDest,yDest,board) ;
                        // verify if it isn't a case where the player can kill and the move isn't a kill
                        if (!(canKill && !wasKill)) {
                            // verify if it isn't a kill or if the kill is the best he can do
                            if (!wasKill || player->isTheBestKillOnBoard(board.getSquare(x,y),x,y,xDest,yDest, board, with_thread)){
                                MOVE move ;
                                move.x = x ;
                                move.y = y ;
                                move.xDest = xDest ;
                                move.yDest = yDest ;
                                // save the move
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

std::vector<CHILD> Game::findChild(const Checkerboard & board, COLOR color, Player* player, int xSelect, int ySelect) {
    std::vector<CHILD> child ;
    child.clear() ;
    std::vector<MOVE> move ;
    if (xSelect!=-1 && ySelect!=-1)
        move = findMoveOnBoardFrom(board,color, player,xSelect,ySelect) ;
    else
        move = findMoveOnBoard(board,color, player) ;
    // for each move possible on the board by player
    for (int i = 0 ; i<(int)move.size() ; i++) {
        if (_stop) exit(EXIT_SUCCESS);
        CHILD test ;
        test.move = move[i] ;
        // copy of the board
        Checkerboard tmp_board(board) ;
        test.board = tmp_board ;
        test.valued = false ;
        test.xSelect = -1 ;
        test.ySelect = -1 ;
        int x = test.move.x ;
        int y = test.move.y ;
        int xDest = test.move.xDest ;
        int yDest = test.move.yDest ;
        bool wasKill = player->isKillOnBoard(tmp_board.getSquare(x,y),x,y,xDest,yDest,tmp_board) ;
        // execute the move on the copy
        bool isWin = player->moveOnBoard(x,y,xDest,yDest,tmp_board) ;
        if(isWin) {
            tmp_board.ghostBuster() ;
        }
        else {
            // indicate the xSelect ySelect if the move isn't finish (if the player can kill other opponenet piece withour his piece)
            if ((wasKill && player->canKillOnBoard(tmp_board.getSquare(xDest,yDest), xDest, yDest, tmp_board))) {
                test.xSelect = xDest ;
                test.ySelect = yDest ;
            }
            else {
                // transform the piece into king if necessary
                if (Tools::isPiece(tmp_board.getSquare(xDest,yDest)) && player->isOnKingLineOnBoard(yDest, tmp_board))
                    tmp_board.setSquare(xDest, yDest, player->king);
                tmp_board.ghostBuster() ;
            }
        }
        // save the child
        child.push_back(test);
    }
    return child ;
}

int Game::findBestChild(std::vector<CHILD> child, std::vector<MOVE> & best, int nb_child_treated) {
    int value = 0 ;
    // for each child treated
    for (int i = 0 ; i<nb_child_treated ; i++) {
        if (i==0 || child[i].value >= value) {
            #pragma omp critical
            {
                if (i==0 || child[i].value > value) {
                    // if it's the first child analysed or if the child have a best value than before
                    // change best value and clear the old moves
                    value = child[i].value ;
                    best.clear();
                }
                // if the child have a best or a similar valur than before
                // add his move to the best moves
                best.push_back(child[i].move) ;
            }
        }
    }
    if (best.empty()) {
        qDebug() << "error" << "findBestChild renvoie un tableau des meilleurs coups vide" ;
    }
    return value ;
}

MOVE Game::negaMax(bool with_thread_param) {
    std::vector<MOVE> m ;
    m.clear() ;
    init_reporting();
    // init the time begin of the IA launching
    gettimeofday(&time_IA_begin , NULL) ;
    // init xSelect ySelect if a piece is currently selected
    int xSelect = -1 ;
    int ySelect = -1 ;
    if (board.selection.select) {
        xSelect = board.selection.x ;
        ySelect = board.selection.y ;
    }
    // launch negamax algorithm with appropriate parameters
    int value ;
    if (isWhiteState(state) && P1->isCP()) {
        if (with_thread_param) {
            value = ((int)WHITE) * negaMaxThread(board, P1->getLevel(), WHITE, P1, P2, m, xSelect, ySelect) ;
        }
        else
            value = ((int)WHITE) * negaMaxClassic(board, P1->getLevel(), WHITE, P1, P2, m,xSelect, ySelect) ;
    }
    if (isBlackState(state) && P2->isCP()) {
        if (with_thread_param) {
            value = ((int)BLACK) * negaMaxThread(board, P2->getLevel(), BLACK, P1, P2, m, xSelect, ySelect) ;
        }
        else
            value = ((int)BLACK) * negaMaxClassic(board, P2->getLevel(), BLACK, P1, P2, m, xSelect, ySelect) ;
    }
    // save reporting if necessary
    if(with_reporting) {save_reporting();}
    // indicate the algorithm execution time
    timeval end ;
    gettimeofday(&end , NULL) ;
    qDebug() <<  "Temps d'exécution = " << Tools::timediff(time_IA_begin,end) ;
    qDebug() << "cost value = " << value ;
    // return error if the algorithm can't find a move
    if (m.empty()) {
        MOVE error ;
        error.x = error.y = error.xDest = error.yDest = -1 ;
        return error ;
    }
    // return a random move in the best moves
    return m[rand()%m.size()];
}

int Game::negaMaxClassic(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int xSelect, int ySelect) {
    // init the current player and opponent simulation
    Player* player = (color==WHITE ? P1 : P2) ;
    int value ;
    std::vector<CHILD> child ;
    child.clear() ;
    // cost function return if the depth is max are if the game is finish on the current board
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color) ;
        // reporting operations if necessary
        if(with_reporting) {
            timeval end ;
            gettimeofday(&end , NULL) ;
            add_node_reporting(board,value,Tools::timediff(time_IA_begin,end),child.size(),child.size()) ;
        }
        return value ;
    }
    // find all the child corresponding with the current node board
    child = findChild(board,color, player, xSelect, ySelect) ;
    // for each childs
    for (int i = 0 ; i<(int)child.size() ; i++) {
        // keep the graphism active
        QCoreApplication::processEvents();
        if (_stop) exit(EXIT_SUCCESS);
        // indicate the threads informations
        if (omp_get_num_threads()>1)
            qDebug() << "nb threads = " << omp_get_num_threads() ;
        // launch algorithm recursively and save cost value
        child[i].value = - negaMaxClassic(child[i].board, depth - 1, (COLOR)(-(int)color),P1, P2, best, child[i].xSelect, child[i].ySelect) ;
    }
    // find the best child(s) and the best move(s) corresponding
    value = findBestChild(child,best,child.size()) ;
    // reporting operations if necessary
    if(with_reporting) {
        timeval end ;
        gettimeofday(&end , NULL) ;
        add_node_reporting(board,value,Tools::timediff(time_IA_begin,end),child.size(),child.size()) ;
    }
    return value ;
}

int Game::negaMaxThread(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best , int xSelect, int ySelect) {
    // init the current player and opponent simulation
    Player* player = (color==WHITE ? P1 : P2) ;
    int value ;
    std::vector<CHILD> child ;
    child.clear() ;
    // cost function return if the depth is max are if the game is finish on the current board
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color) ;
        return value ;
    }
    // find all the child corresponding with the current node board
    child = findChild(board,color, player, xSelect, ySelect) ;

    /*#pragma omp single
    {*/
        // for each chidls
        #pragma omp parallel for
        for (int i = 0 ; i<(int)child.size() ; i++)
        {
            // keep the graphism active
            QCoreApplication::processEvents();
            if (_stop) exit(EXIT_SUCCESS);
            // indicate the threads informations
            if (omp_get_num_threads()>1)
                qDebug() << "nb threads = " << omp_get_num_threads() ;

            #pragma omp task
            // launch algorithm recursively and save cost value
            child[i].value = - negaMaxThread(child[i].board, depth - 1, (COLOR)(-(int)color),P1, P2, best, child[i].xSelect, child[i].ySelect) ;
            //#pragma omp taskwait
        }
    //}
    // find the best child(s) and the best move(s) corresponding
    value = findBestChild(child,best,child.size()) ;
    return value ;
}

MOVE Game::alphaBeta(bool with_thread_param) {
    std::vector<MOVE> m ;
    m.clear();
    init_reporting() ;
    // init the time begin of the IA launching
    gettimeofday(&time_IA_begin , NULL) ;
    // init xSelect ySelect if a piece is currently selected
    int xSelect = -1 ;
    int ySelect = -1 ;
    if (board.selection.select) {
        xSelect = board.selection.x ;
        ySelect = board.selection.y ;
    }
    // launch alphabeta algorithm with appropriate parameters
    int value = 0 ;
    if (isWhiteState(state) && P1->isCP()) {
        if (with_thread_param) {
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
    // save reporting if necessary
    if(with_reporting)save_reporting();
    // indicate the algorithm execution time
    timeval end ;
    gettimeofday(&end , NULL) ;
    qDebug() <<  "Temps d'exécution = " << Tools::timediff(time_IA_begin,end) ;
    // return error if the algorithm can't find a move
    if (m.empty()) {
        MOVE error ;
        error.x = error.y = error.xDest = error.yDest = -1 ;
        return error ;
    }
    // return a random move in the best moves
    return m[rand()%m.size()];
}

int Game::alphaBetaClassic(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec , int xSelect, int ySelect) {
    // init the current player and opponent simulation
    Player* player = (color==WHITE ? P1 : P2) ;
    int value = 0 ;
    std::vector<CHILD> child ;
    child.clear() ;
    int nb_child_treated = 0 ;
    // cost function return if the depth is max are if the game is finish on the current board
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color);
        // reporting operations if necessary
        if(with_reporting) {
            timeval end ;
            gettimeofday(&end , NULL) ;
            add_node_reporting(board,value,Tools::timediff(time_IA_begin,end),child.size(),nb_child_treated) ;
        }
        return value ;
    }
    // find all the child corresponding with the current node board
    child = findChild(board,color, player, xSelect, ySelect) ;
    // begin by considering all childs will be treated
    nb_child_treated = child.size() ;
    bool value_init = false ;
    // treat all the childs needed while nb_child_treated isn't changed
    for (int i = 0 ; i<nb_child_treated ; i++) {
        // keep the graphism active
        QCoreApplication::processEvents();
        if (_stop) exit(EXIT_SUCCESS);
        // nb_child_treated can be stopped if
        // - it isn't the first child treated
        // - the precedent value of tree has been affected (the root of the current node isn't a first child treated)
        // - the current value is already better than the root value, so negatively, in amont, the current root will not be chosen
        if (i!=0 && ismaxprec && value>maxprec && nb_child_treated==(int)child.size()) {
            nb_child_treated = i ;
        }
        else {
            // indicate the threads informations
            if (omp_get_num_threads()>1)
                qDebug() << "nb threads = " << omp_get_num_threads() ;
            // launch algorithm recursively and save cost value
            child[i].value = -alphaBetaClassic(child[i].board, depth - 1, (COLOR)(-(int)color),P1, P2, best, -value, i!=0, child[i].xSelect, child[i].ySelect) ;
            // change current max value if necessary
            if (!value_init) {
                value = child[i].value ;
                value_init = true ;
            }
            else {
                if (value<child[i].value)
                    value = child[i].value ;
            }
        }

    }
    // find the best child(s) and the best move(s) corresponding
    value = findBestChild(child,best,nb_child_treated) ;
    // reporting operations if necessary
    if(with_reporting) {
        timeval end ;
        gettimeofday(&end , NULL) ;
        add_node_reporting(board,value,Tools::timediff(time_IA_begin,end),child.size(),nb_child_treated) ;
    }
    return value ;
}

int Game::alphaBetaThread(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect) {
    // init the current player and opponent simulation
    Player* player = (color==WHITE ? P1 : P2) ;
    int value ;
    std::vector<CHILD> child ;
    child.clear() ;
    int nb_child_treated = 0 ;
    // cost function return if the depth is max are if the game is finish on the current board
    if (depth==0 || isFinishOnBoard(board, player)){
        value = ((int)color) * costFunction(board, player, color);
        return value ;
    }
    // find all the child corresponding with the current node board
    child = findChild(board,color, player, xSelect, ySelect) ;
    // begin by considering all childs will be treated
    nb_child_treated = child.size() ;
    bool value_init = false ;

    /*#pragma omp single
    {*/
        // treat all the childs needed while nb_child_treated isn't changed
        #pragma omp parallel for
        for (int i = 0 ; i<nb_child_treated ; i++)
        {
            // keep the graphism active
            QCoreApplication::processEvents();
            if (_stop) exit(EXIT_SUCCESS);
            // nb_child_treated can be stopped if
            // - it isn't the first child treated
            // - the precedent value of tree has been affected (the root of the current node isn't a first child treated)
            // - the current value is already better than the root value, so negatively, in amont, the current root will not be chosen
            if (i!=0 && ismaxprec && value>maxprec && nb_child_treated==(int)child.size()) {
                nb_child_treated = i ;
            }
            else {
                // indicate the threads informations
                if (omp_get_num_threads()>1)
                    qDebug() << "nb threads = " << omp_get_num_threads() ;

                #pragma omp task
                // launch algorithm recursively and save cost value
                child[i].value = -alphaBetaThread(child[i].board, depth - 1, (COLOR)(-(int)color),P1, P2, best, -value, i!=0, child[i].xSelect, child[i].ySelect) ;
                // #pragma omp taskwait

                #pragma omp critical
                {
                    // change current max value if necessary
                    if (!value_init) {
                        value = child[i].value ;
                        value_init = true ;
                    }
                    else {
                        if (value<child[i].value)
                            value = child[i].value ;
                    }
                }
            }
        }
    //}
    // find the best child(s) and the best move(s) corresponding
    value = findBestChild(child,best,nb_child_treated) ;
    return value ;
}

Player* Game::playerTurn() {
    return (state == WHITE_SELECT || state == WHITE_DEST ? P1 : P2) ;
}

void Game::init_reporting() {
    reporting.clear();
}

void Game::add_node_reporting(const Checkerboard & board, int value, double time, int nb_child, int nb_child_treated) {
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << nb_child_treated) )->str() ) ;
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << nb_child) )->str() ) ;
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << (long long int)time) )->str() ) ;
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << value) )->str() ) ;
    reporting.push_back(board.toString()) ;
}

void Game:: save_reporting() {
    std::reverse(reporting.begin(),reporting.end());
    QFile fichier(this->url_reporting);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    flux<<board.getSize();
    flux<<";";
    qDebug() << "size reporting = " << reporting.size() ;
    for (int i=0; i<(int)reporting.size();i++){
        QString res =QString::fromStdString(reporting[i]);
        flux<<res;
        flux<<";";
    }
    fichier.close();
}

//Gestion de l'arret en cours de calcul de l'IA lors de la fermeture de la fenetre
void Game::stop(){
    _stop = true;
}
