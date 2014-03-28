#include "game.h"


Game::Game() {


}


Game::~Game() {
        delete board ;
        delete P1 ;
        delete P2 ;
}

// create game with dimension parameters
void Game::init()
{
        winner = 0 ;
        // init board
        board = new Checkerboard(size) ;

        // init players
        P1 = new PlayerManual(nbLinePiece1, board, NORD) ;
        P2 = new PlayerManual(nbLinePiece2, board, SUD) ;
}

// launch the game
void Game::launch() {

        if (winner!=0)
            qDebug() << "winner : player " << winner << endl ;
        else {
            //Clean the terminal
            //system("cls");
            qDebug() << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
                         << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
                             << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl ;

            qDebug() << "Player1" << endl << endl ;
            // delete pieces which have been killed during last turn
            board->ghostBuster() ;
            //Player 1 turn
            // board printing
            board->print() ;
            // piece selection
            qDebug() << "select (ex : A1) :   " ;
            nextEvent = &selectPieceP1Event ;
        }


}

// print game
void Game::print()
{
        board->print() ;
}

void Game::start() {
    // choice of developping mode
    qDebug() << "mode : " << endl << "1	dev game" << endl << "2	dev graphic" << endl ;
    nextEvent = &modeDevEvent ;
}

QString Game::input() {
    QString s = in ;
    in = "" ;
    return s ;
}

void Game::read(QLineEdit* txt) {
    in = txt->text();
    txt->clear();
    if (nextEvent!=NULL)
        nextEvent(this) ;
}

void Game::modeDev() {
    int s = input().toInt() ;
    switch(s) {
        case 1 :    // main for game developping
                    qDebug() << "main Game" << endl ;
                    // menu
                    qDebug() << "1	classic game" ;
                    qDebug() << "2	custom game" ;
                    nextEvent = &modeGameEvent ;
                    break ;
        case 2 :    qDebug() << "2" ;
                    qDebug() << "Board Size : " ;
                    break ;
    }
}

void Game::modeGame() {
    int s = input().toInt() ;
    switch(s) {
        case 1 :    size = 10 ;
                    nbLinePiece1 = 4 ;
                    nbLinePiece2 = 4 ;
                    // create game
                    init() ;
                    // launch game
                    launch() ;
                    break ;
        case 2 :    qDebug() << "Board Size : " ;
                    nextEvent = &sizeInitEvent ;
                    break ;
        default :   return ;
    }
}

void Game::sizeInit() {
    int s = input().toInt() ;
    if (s>=MIN_SIZE && isEven(s)) {
        size = s ;
        // init number of pieces with user input
        qDebug() << endl << "Number of pieces lines" ;
        qDebug() << "for player1 : " ;
        nextEvent = &nbPieceP1Event ;
    }
}

void Game::nbPieceP1(){
    int s = input().toInt() ;
    if (s>0 && s<size/2) {
            nbLinePiece1 = s ;
            qDebug() << "for player2 : " ;
            nextEvent = &nbPieceP2Event ;
    }
}

void Game::nbPieceP2(){
    int s = input().toInt() ;
    if (s>0 && s<size/2) {
            nbLinePiece2 = s ;
            // create game
            init() ;
            // launch game
            launch() ;
    }
}

void Game::selectPieceP1(){
    QString s = input() ;
    int x = letter_to_num_column(s.at(0)) ;
    int y = s.remove(0,1).toInt() ;

    if (x>0 && x<=board->getSize() && y>0 && y<=board->getSize()) {
        // transform x and y value for table indice
        x-- ;
        y-- ;
        if (P1->selectValid(x,y)) {
            P1->x = x ;
            P1->y = y ;
            qDebug() << "destination : (ex : A1) :   " ;
            nextEvent = &selectDestP1Event ;
        }
    }
}

void Game::selectPieceP2(){
    QString s = input() ;
    int x = letter_to_num_column(s.at(0)) ;
    int y = s.remove(0,1).toInt() ;
    if (x>0 && x<=board->getSize() && y>0 && y<=board->getSize()) {
        // transform x and y value for table indice
        x-- ;
        y-- ;
        if (P2->selectValid(x,y)) {
            P2->x = x ;
            P2->y = y ;
            qDebug() << "destination : (ex : A1) :   " ;
            nextEvent = &selectDestP2Event ;
        }
    }
}

void Game::selectDestP1() {
    QString s = input() ;
    int xDest = letter_to_num_column(s.at(0)) ;
    int yDest = s.remove(0,1).toInt() ;
    if (xDest>0 && xDest<=board->getSize() && yDest>0 && yDest<=board->getSize()) {
        // transform x and y value for table indice
        xDest-- ;
        yDest-- ;
        bool canKill = P1->haveKillOn(*board) ;
        bool valid = P1->destValid(xDest,yDest) && P1->isMoveValid(board->getSquare()[P1->x][P1->y],P1->x,P1->y,xDest,yDest) ;
        if (valid) {
            bool wasKill = P1->isKill(board->getSquare()[P1->x][P1->y],P1->x,P1->y,xDest,yDest) ;
            if(!(valid=!(canKill && !wasKill))) {
                    qDebug() << endl << "You have to kill !" << endl ;
                    qDebug() << "select (ex : A1) :   " ;
                    nextEvent = &selectPieceP1Event ;
                    return ;
            }
            P1->xDest = xDest ;
            P1->yDest = yDest ;
            if(P1->move(P1->x,P1->y,P1->xDest,P1->yDest))
                winner = 1 ;
            else {
                P1->x = P1->xDest ;
                P1->y = P1->yDest ;
                if (!(wasKill && P1->canKillOn(board->getSquare()[P1->x][P1->y], P1->x, P1->y, *board))) {
                    if (isPiece(board->getSquare()[P1->x][P1->y]) && P1->isOnKingLine(P1->y))
                        board->setSquare(P1->x, P1->y, P1->king);
                    }
                    qDebug() << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
                                 << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
                                     << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl ;

                    qDebug() << "Player2" << endl << endl ;
                    // delete pieces which have been killed during last turn
                    board->ghostBuster() ;
                    //Player 1 turn
                    // board printing
                    board->print() ;
                    // piece selection
                    qDebug() << "select (ex : A1) :   " ;
                    nextEvent = &selectPieceP2Event ;
                }
            }
        }
    }


void Game::selectDestP2() {
    QString s = input() ;
    int xDest = letter_to_num_column(s.at(0)) ;
    int yDest = s.remove(0,1).toInt() ;
    if (xDest>0 && xDest<=board->getSize() && yDest>0 && yDest<=board->getSize()) {
        // transform x and y value for table indice
        xDest-- ;
        yDest-- ;
        bool canKill = P2->haveKillOn(*board) ;
        bool valid = P2->destValid(xDest,yDest) && P2->isMoveValid(board->getSquare()[P2->x][P2->y],P2->x,P2->y,xDest,yDest) ;
        if (valid) {
            bool wasKill = P2->isKill(board->getSquare()[P2->x][P2->y],P2->x,P2->y,xDest,yDest) ;
            if(!(valid=!(canKill && !wasKill))) {
                    qDebug() << endl << "You have to kill !" << endl ;
                    qDebug() << "select (ex : A1) :   " ;
                    nextEvent = &selectPieceP2Event ;
                    return ;
            }
            P2->xDest = xDest ;
            P2->yDest = yDest ;
            if(P2->move(P2->x,P2->y,P2->xDest,P2->yDest))
                winner = 2 ;
            else {
                P2->x = P2->xDest ;
                P2->y = P2->yDest ;
                if (!(wasKill && P2->canKillOn(board->getSquare()[P2->x][P2->y], P2->x, P2->y, *board))) {
                    if (isPiece(board->getSquare()[P2->x][P2->y]) && P2->isOnKingLine(P2->y))
                        board->setSquare(P2->x, P2->y, P2->king);
                    }
                    qDebug() << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
                                 << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
                                     << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl ;

                    qDebug() << "Player1" << endl << endl ;
                    // delete pieces which have been killed during last turn
                    board->ghostBuster() ;
                    //Player 1 turn
                    // board printing
                    board->print() ;
                    // piece selection
                    qDebug() << "select (ex : A1) :   " ;
                    nextEvent = &selectPieceP1Event ;
                }
            }
        }
    }



///////////////////////////////////////////////////////////////////////////////////////////////////////////

void modeDevEvent(Game* game) {
    game->modeDev() ;
}

void modeGameEvent(Game* game) {
    game->modeGame() ;
}

void sizeInitEvent(Game* game) {
    game->sizeInit() ;
}

void nbPieceP1Event(Game* game){
    game->nbPieceP1() ;
}

void nbPieceP2Event(Game* game){
    game->nbPieceP2() ;
}

void selectPieceP1Event(Game* game){
    game->selectPieceP1() ;
}

void selectPieceP2Event(Game* game){
    game->selectPieceP2() ;
}

void selectDestP1Event(Game* game) {
    game->selectDestP1() ;
}

void selectDestP2Event(Game* game) {
    game->selectDestP2() ;
}

/*


// main for graphic developping
int mainGraphic() {

    qDebug() << "main Graphic" << endl ;

    // game creation
    Game game(10,4,4) ;

    // game printing
    game.print() ;

    return 0 ;

}
*/

