#include "stdafx.h"
#include <iostream>
#include "main.h"
#include "Game.h"

using namespace std;

// main for game developping
int mainGame() {

	cout << "main Game" << endl ;

	// game creation
	Game game(10,10) ;

	// game printing
	game.print() ;

	// wait key press
	getchar() ;
	getchar() ;

	return 0 ;

}

// main for graphic developping
int mainGraphic() {

	cout << "main Graphic" << endl ;

	// game creation
	Game game(10,10) ;

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