#include "main.h"


/*
// parameters scan menu for custom game
void customization(int & size, int & nbLinePiece1, int & nbLinePiece2) {
		// init board size with user input
        qDebug() << "Board Size : " ;
		do {
			size = scanInt() ;
		} while (size<MIN_SIZE || !isEven(size)) ;
		// init number of pieces with user input
        qDebug() << endl << "Number of pieces lines" << endl ;
        qDebug() << "for player1 : " ;
		do {
			nbLinePiece1 = scanInt() ;
		} while (nbLinePiece1<=0 || nbLinePiece1>=size/2) ;
        qDebug() << "for player2 : " ;
		do {
			nbLinePiece2 = scanInt() ;
		} while (nbLinePiece2<=0 || nbLinePiece2>=size/2) ;
}

// main for game developping
int mainGame() {
	char choice ;
	int size ;
	int nbLinePiece1 ;
	int nbLinePiece2 ;
	Game* game ;

    qDebug() << "main Game" << endl << endl ;
	
	do {
		// menu
        qDebug() << "1	classic game" << endl ;
        qDebug() << "2	custom game" << endl ;
        qDebug() << "3	quit" << endl ;
		do {
			cin >> choice ;
		} while (choice!='1' && choice!='2' && choice!='3') ;

		// if choice isn't quit
		if (choice!='3') {

			if (choice=='1') {
				size = 10 ;
				nbLinePiece1 = 4 ;
				nbLinePiece2 = 4 ;
			}

			if (choice=='2')
				customization(size, nbLinePiece1, nbLinePiece2) ;

			// create game
			game = new Game(size, nbLinePiece1, nbLinePiece2) ;

			// launch game
			game->launch() ;

			delete game ;
		}
	} while (choice!='3') ;

	return 0 ;

}

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


QString read() {
    QString s = in ;
    in = "" ;
    return s ;
}

bool read(QString s) {
    if (in==s) {
        in = "" ;
        return true ;
    }
    return false ;
}

void modeChoice() {
    if (read("1")) {
        qDebug() << "1" ;
        //mainGame() ;
    }
    else {
        if (read("2")) {
            qDebug() << "2" ;
            //mainGraphic() ;
        }
    }
}

void start() {
    // choice of developping mode
    qDebug() << "mode : " << endl << "1	dev game" << endl << "2	dev graphic" << endl ;
    next = &modeChoice ;
}


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show() ;
    return a.exec() ;
}


