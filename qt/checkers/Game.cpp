#include "game.h"


Game::Game(int size, int nbLineP1, int nbLineP2) {
    this->size = size ;
    this->nbLinePiece1 = nbLineP1 ;
    this->nbLinePiece2 = nbLineP2 ;
    winner = 0 ;
    // init board
    board = new Checkerboard(size) ;
    // init players
    P1 = new PlayerManual(nbLinePiece1, board, NORD) ;
    P2 = new PlayerManual(nbLinePiece2, board, SUD) ;
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


QString Game::input() {
    QString s = in ;
    in = "" ;
    return s ;
}

void Game::clickOnBoard(QLineEdit* ok_tb) {

    in = ok_tb->text();
    ok_tb->clear();
    QString s = input() ;
    int x = letter_to_num_column(s.at(0)) ;
    int y = s.remove(0,1).toInt() ;
    qDebug() << "point x : " << x << ", y : " << y << endl;

    switch (state) {
        case WHITE_SELECT :     state = select(P1, x, y) ;
                                break ;
        case WHITE_DEST :       state = dest(P1, P2, x, y) ;
                                break ;
        case BLACK_SELECT :     state = select(P2, x, y) ;
                                break ;
        case BLACK_DEST :       state = dest(P2, P1, x, y) ;
                                break ;
        case END :              txt += "Winner : " + winner ;
                                break ;
    }
}

void Game::clickOnBoard(int x, int y){

       switch (state) {
        case WHITE_SELECT :     state = select(P1, x, y) ;
                                break ;
        case WHITE_DEST :       state = dest(P1, P2, x, y) ;
                                break ;
        case BLACK_SELECT :     state = select(P2, x, y) ;
                                break ;
        case BLACK_DEST :       state = dest(P2, P1, x, y) ;
                                break ;
        case END :              txt += "Winner : " + winner ;
                                break ;
    }
}

STATE Game::select(Player* player, int x, int y) {

    if (x>0 && x<=board->getSize() && y>0 && y<=board->getSize()) {
        // transform x and y value for table indice
        x-- ;
        y-- ;
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
    if (xDest>0 && xDest<=board->getSize() && yDest>0 && yDest<=board->getSize()) {
        // transform x and y value for table indice
        xDest-- ;
        yDest-- ;
        bool canKill = player->haveKillOnBoard(board) ;
        bool valid = player->isMoveValidOnBoard(board->getSquare()[player->x][player->y].square,player->x,player->y,xDest,yDest, board) ;
        if (valid) {
            bool wasKill = player->isKillOnBoard(board->getSquare()[player->x][player->y].square,player->x,player->y,xDest,yDest,board) ;
            if(!(valid=!(canKill && !wasKill))) {
                    txt += "\nYou have to kill !\n" ;
                    txt += "select (ex : A1) :   " ;
                    board->deselect();
                    return player->state_select ;
            }
            else {
                if (!(valid = !wasKill || player->isTheBestKillOnBoard(board->getSquare()[player->x][player->y].square,player->x,player->y,xDest,yDest, board))) {
                    txt += "\nYou have to choose the best kill !\n" ;
                    txt += "select (ex : A1) :   " ;
                    return player->state_select ;
                }
            }
            player->xDest = xDest ;
            player->yDest = yDest ;
            if(player->moveOnBoard(player->x,player->y,player->xDest,player->yDest, board)) {
                winner = 1 ;
                return END ;
            }
            else {
                player->x = player->xDest ;
                player->y = player->yDest ;
                if ((wasKill && player->canKillOnBoard(board->getSquare()[player->x][player->y].square, player->x, player->y, board))) {
                    qDebug() << "You have an other kill" << endl ;
                    return state ;
                }
                else {
                    if (isPiece(board->getSquare()[player->x][player->y].square) && player->isOnKingLineOnBoard(player->y, board))
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
    board->paint(board_gl) ;
}
