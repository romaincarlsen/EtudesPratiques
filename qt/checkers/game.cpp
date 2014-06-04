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

Player* Game::getCurrentPlayer(){
    if(isWhiteState(state)) return getP1();
    else return getP2();
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
    return !board.isCurrentKill() && (board.isWin() || isEqualityOnBoard(board, player)) ;
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
    bool res = false ;
    // if there isn't, the piece is deselected and the player have to select another
    if(!board.isCurrentKill()){
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
int Game::costFunction(const Checkerboard & board, COLOR color) {
    switch (playerTurn()->costFunction) {
    case 1:
        return costFunction1(board, color);
        break;
    case 2:
        return costFunction2(board, color);
        break;
    case 3:
        return costFunction3(board, color);
        break;
    case 4:
        return costFunction4(board, color);
        break;
    case 5:
        return costFunction5(board, color);
        break;
    default:
        return costFunction1(board, color);
        break;
    }
}

int Game::costFunction1(const Checkerboard & board, COLOR color) {
    Player* player = playerTurn() ;
    int nega = (player->isWhite() && color==WHITE) || (player->isBlack() && color==BLACK) ? 1 : -1 ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    return nega * (nbMinePiece - nbOpponentPiece + (nbMineKing - nbOpponentKing)*3) ;
}

int Game::costFunction2(const Checkerboard & board, COLOR color) {
    Player* player = playerTurn() ;
    int nega = (player->isWhite() && color==WHITE) || (player->isBlack() && color==BLACK) ? 1 : -1 ;
    int nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing ;
    player->scanNumberOfOnBoard(nbMinePiece, nbMineKing, nbOpponentPiece, nbOpponentKing, board) ;
    int value = (nbMinePiece - nbOpponentPiece)*10 + (nbMineKing - nbOpponentKing)*50 ;
    value -= ((nbMinePiece + nbMineKing)==0)*100 ;
    value += ((nbOpponentPiece + nbOpponentKing)==0)*100 ;
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
            if (player->isOpponent(board.getSquare(x,y))) {
                if (x+1<board.getSize() && y+1<board.getSize())
                    value -= player->isOpponent(board.getSquare(x+1,y+1)) ;
                if (x-1>=0 && y+1<board.getSize())
                    value -= player->isOpponent(board.getSquare(x-1,y+1)) ;
                if (x-1>=0 && y-1>=0)
                    value -= player->isOpponent(board.getSquare(x-1,y-1)) ;
                if (x+1<board.getSize() && y-1>=0)
                    value -= player->isOpponent(board.getSquare(x+1,y-1)) ;
            }
        }
    }
    return nega * value ;
}

int Game::costFunction3(const Checkerboard & board, COLOR color) {
    Player* player = playerTurn() ;
    int nega = (player->isWhite() && color==WHITE) || (player->isBlack() && color==BLACK) ? 1 : -1 ;
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
    return nega * value ;
}

int Game::costFunction4(const Checkerboard & board, COLOR color) {
    return 0 ;
}

int Game::costFunction5(const Checkerboard & board, COLOR color) {
    return (rand()%201 - 100) ;
}

std::vector<MOVE> Game::findMoveOnBoard(const Checkerboard & board, COLOR color, Player* player) {
    std::vector<MOVE> m ;
    m.clear();
    bool canKill = player->haveKillOnBoard(board) ;
    // for each piece to move
    for (int x=0 ; x<board.getSize() ; x++) {
        for (int y=0 ; y<board.getSize() ; y++) {
            if ((Tools::isWhite(board.getSquare(x,y)) && color==WHITE) || (Tools::isBlack(board.getSquare(x,y)) && color==BLACK)) {
                if (player->selectValidOnBoard(x,y, board)) {
                    // for each destination corresponding
                    for (int xDest=0 ; xDest<board.getSize() ; xDest++) {
                        for (int yDest=0 ; yDest<board.getSize() ; yDest++) {
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

std::vector<MOVE> Game::findMoveOnBoardFrom(const Checkerboard & board, COLOR color, Player* player, int x, int y) {
    std::vector<MOVE> m ;
    m.clear();

    if ((Tools::isWhite(board.getSquare(x,y)) && color==WHITE) || (Tools::isBlack(board.getSquare(x,y)) && color==BLACK)) {
        if (player->selectValidOnBoard(x,y, board)) {
            bool canKill = player->haveKillOnBoardFrom(board, x,y) ;
            // for each destination corresponding from xSelect ySelect
            for (int xDest=0 ; xDest<board.getSize() ; xDest++) {
                for (int yDest=0 ; yDest<board.getSize() ; yDest++) {
                    if (player->isMoveValidOnBoard(board.getSquare(x,y),x,y,xDest,yDest, board)) {
                        bool wasKill = player->isKillOnBoard(board.getSquare(x,y),x,y,xDest,yDest,board) ;
                        // verify if it isn't a case where the player can kill and the move isn't a kill
                        if (!(canKill && !wasKill)) {
                            // verify if it isn't a kill or if the kill is the best he can do
                            if (!wasKill || player->isTheBestKillOnBoardFrom(board.getSquare(x,y),x,y,xDest,yDest, board, with_thread)){
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
    if (xSelect!=-1 && ySelect!=-1) {
        move = findMoveOnBoardFrom(board,color, player,xSelect,ySelect) ;
    }
    else
        move = findMoveOnBoard(board,color, player) ;
    // for each move possible on the board by player
    for (unsigned int i = 0 ; i<move.size() ; i++) {
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
        bool wasKill = player->isKillOnBoard(test.board.getSquare(x,y),x,y,xDest,yDest,test.board) ;
        // execute the move on the copy
        bool isWin = player->moveOnBoard(x,y,xDest,yDest,test.board) ;
        if(isWin) {
            test.board.ghostBuster() ;
            // save the child
            child.push_back(test);
        }
        else {
            // indicate the xSelect ySelect if the move isn't finish (if the player can kill other opponenet piece withour his piece)
            if ((wasKill && player->canKillOnBoard(test.board.getSquare(xDest,yDest), xDest, yDest, test.board))) {
                test.xSelect = xDest ;
                test.ySelect = yDest ;
                std::vector<CHILD> next =  findChild(test.board, color, player, xDest, yDest) ;
                for (unsigned int n=0 ; n<next.size() ; n++) {
                    test.board = next[n].board ;
                    // save the child
                    child.push_back(test);
                }
            }
            else {
                // transform the piece into king if necessary
                if (Tools::isPiece(test.board.getSquare(xDest,yDest)) && player->isOnKingLineOnBoard(yDest, test.board))
                    test.board.setSquare(xDest, yDest, player->king);
                test.board.ghostBuster() ;
                // save the child
                child.push_back(test);
            }
        }
    }
    return child ;
}

int Game::findBestChild(std::vector<CHILD> child, std::vector<MOVE> & best, int depth) {
    int value = 99999999 ;
    if (child.empty()) {
        qDebug() << "error : child is empty" ;
    }
    bool value_init = false ;
    // for each child treated
    for (unsigned int i = 0 ; i<child.size() ; i++) {
        if (!value_init || (child[i].valued && child[i].value >= value)) {
            if (!value_init || (child[i].valued && child[i].value > value)) {
                // if it's the first child analysed or if the child have a best value than before
                // change best value and clear the old moves
                value = child[i].value ;
                value_init = true ;
                if (depth = playerTurn()->getLevel())
                    best.clear();
            }
            // if the child have a best or a similar valur than before
            // add his move to the best moves
            if (depth = playerTurn()->getLevel())
                best.push_back(child[i].move) ;
        }
    }
    if (depth = playerTurn()->getLevel()) {
        if (best.empty()) {
            qDebug() << "error" << "tableau des meilleurs coups vide" ;
        }
    }
    return value ;
}

MOVE Game::negaMax() {
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
        #pragma omp parallel if(with_thread)
        {
            #pragma omp single
            value = negaMax(board, P1->getLevel(), WHITE, P1, P2, m,-value,false, xSelect, ySelect) ;
        }
    }
    if (isBlackState(state) && P2->isCP()) {
        #pragma omp parallel if(with_thread)
        {
            #pragma omp single
            value = negaMax(board, P2->getLevel(), BLACK, P1, P2, m,-value,false, xSelect, ySelect) ;
        }
    }

    // save reporting if necessary
    if(with_reporting && !with_thread)save_reporting();
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
    MOVE choice = m[rand()%m.size()] ;
    if (board.selection.select) {
        choice.x = -1 ;
        choice.y = -1 ;
    }
    // return a random move in the best moves
    return choice ;
}

int Game::negaMax(const Checkerboard & board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best, int maxprec, bool ismaxprec, int xSelect, int ySelect) {
    // init the current player and opponent simulation
    Player* player = (color==WHITE ? P1 : P2) ;
    int value = 999999 ;
    // find all the child corresponding with the current node board
    std::vector<CHILD> child = findChild(board,color, player, xSelect, ySelect) ;
    // cost function return if the depth is max are if the game is finish on the current board
    if (depth==0 || board.isWin() || child.size()==0){
        value = costFunction(board, color);
        if(with_reporting && !with_thread) {
            timeval end ;
            gettimeofday(&end , NULL) ;
            add_node_reporting(board,value,Tools::timediff(time_IA_begin,end),0,0) ;
        }
        return value ;
    }
    // begin by considering all childs will be treated
    bool loop_cut = false ;
    bool value_init = false ;
    int nb_child_treated = 0 ;
    // treat all the childs needed while nb_child_treated isn't changed
    for (int i = 0 ; i<child.size() ; i++)
    {
        // keep the graphism active
        QCoreApplication::processEvents();
        if (_stop) exit(EXIT_SUCCESS);
        // nb_child_treated can be stopped if
        // - it isn't the first child treated
        // - the precedent value of tree has been affected (the root of the current node isn't a first child treated)
        // - the current value is already better than the root value, so negatively, in amont, the current root will not be chosen
        if (!loop_cut || !with_alphabeta) {
            if (with_alphabeta && value_init && ismaxprec && value>maxprec) {
                loop_cut = true ;
            }
            else {
                // indicate the threads informations
                /*if (omp_get_num_threads()>1)
                    qDebug() << "nb threads = " << omp_get_num_threads() ;*/

                // launch algorithm recursively and save cost value
                #pragma omp task shared(child,best,nb_child_treated,value_init,value,loop_cut) if(with_thread)
                {
                    child[i].value = -negaMax(child[i].board, depth - 1, (COLOR)(-color),P1, P2, best, -value, value_init, child[i].xSelect, child[i].ySelect) ;
                    child[i].valued = true ;
                    if (with_alphabeta) {
                        #pragma omp critical
                        {
                            nb_child_treated++ ;
                            // change current max value if necessary
                            if (!value_init) {
                                value = child[i].value ;
                                value_init = true ;
                            }
                            else {
                                if (value<child[i].value) {
                                    value = child[i].value ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    #pragma omp taskwait

    // find the best child(s) and the best move(s) corresponding
    value = findBestChild(child,best,depth) ;

    // reporting operations if necessary
    if(with_reporting && !with_thread) {
        timeval end ;
        gettimeofday(&end , NULL) ;
        add_node_reporting(board,value,Tools::timediff(time_IA_begin,end),child.size(),nb_child_treated) ;
    }
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
    reporting.push_back(static_cast<ostringstream*>( &(ostringstream() << -value) )->str() ) ;
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
    for (unsigned int i=0; i<reporting.size();i++){
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
