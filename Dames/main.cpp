#include "stdafx.h"
#include "main.h"

#include "Game.h"

// parameters scan menu for custom game
void customization(int & size, int & nbLinePiece1, int & nbLinePiece2) {
		// init board size with user input
		cout << "Board Size : " ;
		do {
			size = scanInt() ;
		} while (size<MIN_SIZE || !isEven(size)) ;
		// init number of pieces with user input
		cout << endl << "Number of pieces lines" << endl ;
		cout << "for player1 : " ;
		do {
			nbLinePiece1 = scanInt() ;
		} while (nbLinePiece1<=0 || nbLinePiece1>=size/2) ;
		cout << "for player2 : " ;
		do {
			nbLinePiece2 = scanInt() ;
		} while (nbLinePiece2<=0 || nbLinePiece2>=size/2) ;
}

// main for game developping
int mainGame() {
	char choice ;
	int size = 10 ;
	int nbLinePiece1 = 4 ;
	int nbLinePiece2 = 4;
	Game* game ;

	cout << "main Game" << endl << endl ;
	
	do {
		// menu
		cout << "1	classic game" << endl ;
		cout << "2	custom game" << endl ;
		cout << "3	quit" << endl ;
		do {
			cin >> choice ;
		} while (choice!='1' && choice!='2' && choice!='3') ;

		// if choice isn't quit
		if (choice!='3') {

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

	cout << "main Graphic" << endl ;

	// game creation
	Game game(10,4,4) ;

	// game printing
	game.print() ;

	// wait key press
	getchar() ;
	getchar() ;

	return 0 ;

}


// original main
int main() {

	// choice of developping mode
	char choice ;
	cout << "mode : " << endl << "1	dev game" << endl << "2	dev graphic" << endl ;
	do {
		cin >> choice ;
	}
	while (choice != '1' && choice != '2') ;
	
	// developping mode launching
	if (choice == '1')
		return mainGame() ;
	else
		return mainGraphic() ;
}