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
    return isWhiteState(state) && P1->isCP() || isBlackState(state) && P2->isCP() ;
}

bool Game::isFinish() {
    return state == END ;
}

MOVE Game::negaMax() {
    std::vector<MOVE> m ;
    m.resize(0);

    int value ;
    if (isWhiteState(state) && P1->isCP()) {
        value = ((int)WHITE) * negaMax(board, P1->getLevel(), WHITE, P1, P2, m) ;
    }
    if (isBlackState(state) && P2->isCP()) {

        value = ((int)BLACK) * negaMax(board, P2->getLevel(), BLACK, P1, P2, m) ;

    }
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
int Game::negaMax(Checkerboard* board, int depth, COLOR color, Player* P1, Player* P2, std::vector<MOVE> & best) {
    Player* player = (color==WHITE ? P1 : P2) ;
    Player* opponent = (color==WHITE ? P2 : P1) ;

    if (depth==0 || board->isWin()){
        return ((int)color) * costFunction(board, player, color);
    }
    std::vector<MOVE> move = findMoveOnBoard(board,color, player) ;

    int value ;
    if (move.size()>0) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[0].x,move[0].y,move[0].xDest,move[0].yDest,child) ;
        value = -negaMax(child, depth - 1, (COLOR)(-(int)color), P1, P2, best) ;
        if (depth == playerTurn()->getLevel()) {
            best.resize(best.size()+1) ;
            best[best.size()-1] = move[0] ;
        }
        delete child ;
    }
    for (int i = 1 ; i<move.size() ; i++) {
        Checkerboard* child = new Checkerboard(board) ;
        player->moveOnBoard(move[i].x,move[i].y,move[i].xDest,move[i].yDest,child) ;
        int value_child = -negaMax(child, depth - 1, (COLOR)(-(int)color),P1, P2, best) ;
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
    return value ;
}

Player* Game::playerTurn() {
    return (state == WHITE_SELECT || state == WHITE_DEST ? P1 : P2) ;
}
