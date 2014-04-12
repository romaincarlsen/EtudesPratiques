#include "game.h"


Game::Game(int size, int nbLineP1, int nbLineP2) {
    this->size = size ;
    this->nbLinePiece1 = nbLineP1 ;
    this->nbLinePiece2 = nbLineP2 ;
    winner = 0 ;
    // init board
    board = new Checkerboard(size) ;
    // init players
    P1 = new Player(nbLinePiece1, board, NORD) ;
    P2 = new PlayerCP(nbLinePiece2, board, SUD, 1) ;
    // current state of game loop in state machine

    txt = P1->toString() + "\n\n" ;
    // delete pieces which have been killed during last turn
    board->ghostBuster() ;
    //Player 1 turn
    // board printing
    txt += board->toString() ;
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
    MOVE m ;
    m.x = m.y = m.xDest = m.yDest = -1 ;
    int value ;
    if (isWhiteState(state) && P1->isCP())
        value = -P1->negaMax(board, P1->getLevel(), WHITE, m) ;
    if (isBlackState(state) && P2->isCP())
        value = P2->negaMax(board, P2->getLevel(), BLACK, m) ;
    return m;
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
                    qDebug() << "You have an other kill" << endl ;
                    return state ;
                }
                else {
                    if (Tools::isPiece(board->getSquare(player->x,player->y)) && player->isOnKingLineOnBoard(player->y, board))
                       board->setSquare(player->x, player->y, player->king);
                }

                txt = opponent->toString() + "\n\n" ;
                // delete pieces which have been killed during last turn
                board->ghostBuster() ;
                // board printing
                txt += board->toString() ;
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

    qDebug() << state << endl ;

    board->paint(board_gl) ;
}
