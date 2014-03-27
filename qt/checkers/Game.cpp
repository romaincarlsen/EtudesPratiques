#include "Game.h"

// create game with dimension parameters
Game::Game(int size, int nbLinePiece1, int nbLinePiece2)
{
		// init board
		board = new Checkerboard(size) ;

		// init players
		P1 = new PlayerManual(nbLinePiece1, board, NORD) ;
		P2 = new PlayerManual(nbLinePiece2, board, SUD) ;
}


Game::~Game()
{
		delete board ;
		delete P1 ;
		delete P2 ;
}

// launch the game
void Game::launch()
{		//Indicates the winner (value is 0 if the game is not finished) 
		int winner = 0 ;
		while (winner==0) {
			//Clean the terminal
			system("cls");
            qDebug() << "Player1" << endl << endl ;
			// delete pieces which have been killed during last turn
			board->ghostBuster() ;
			//Player 1 turn
			if (P1->play())
				//Indicate If the player 1 win
				winner = 1 ;
			else {
				system("cls");
                qDebug() << "Player2" << endl << endl ;
				// delete pieces which have been killed during last turn
				board->ghostBuster() ;
				//Player 2 turn
				if(P2->play())
					//Indicate If the player 2 win
					winner = 2 ;
				}
		}
        qDebug() << "winner : player " << winner << endl ;
}

// print game
void Game::print()
{
		board->print() ;
}

