#include "Tools.h"

bool Tools::isWhite(SQUARE square) {
    return square == WHITE_KING || square == WHITE_PIECE;
}

bool Tools::isBlack(SQUARE square) {
    return square == BLACK_KING || square == BLACK_PIECE ;
}

// return if val is even number
bool Tools::isEven(int val) {
    return val%2==0 ;
}

// return if val is odd number
bool Tools::isOdd(int val) {
    return val%2==1 ;
}

// return if square is locked (white square)
bool Tools::isLocked(SQUARE square) {
    return square == LOCK ;
}

// return if the square contain a king
bool Tools::isKing(SQUARE square) {
    return square == WHITE_KING || square ==BLACK_KING ;
}

// return if the square contain a piece
bool Tools::isPiece(SQUARE square) {
    return square == WHITE_PIECE || square ==BLACK_PIECE ;
}

// return if the square is occuped
bool Tools::isNotEmpty(SQUARE square) {
    return square != EMPTY && square !=LOCK ;
}

// return char corresponding to square type for consol printing
char Tools::square_to_char(SQUARE square) {
    switch (square) {
        case BLACK_KING :	return 'O' ;
        case BLACK_PIECE :	return 'o' ;
        case EMPTY :		return 'v' ;
        case WHITE_PIECE :	return 'x' ;
        case WHITE_KING :	return 'X' ;
        case LOCK :			return '#' ;
        default :			return 'e' ;
    }
}


// return img corresponding to square type for consol printing
QPixmap Tools::square_to_img(SQUARE square) {
    switch (square) {
        case BLACK_KING :	return QPixmap("../checkers/img/black_king.png") ;
        case BLACK_PIECE :	return QPixmap("../checkers/img/black_piece.png") ;
        case EMPTY :		return QPixmap("../checkers/img/empty.png") ;
        case WHITE_PIECE :	return QPixmap("../checkers/img/white_piece.png") ;
        case WHITE_KING :	return QPixmap("../checkers/img/white_king.png") ;
        case LOCK :			return QPixmap("../checkers/img/lock.png") ;
        case GHOST :		return QPixmap("../checkers/img/ghost.png") ;
        default :			return QPixmap() ;
    }
}

// return column letter corresponding to column number for consol printing
QChar Tools::num_to_letter_column(int num) {
    return QChar((short)(65+num-1)) ;
}

//return column number corresponding to column letter for consol printing
int Tools::letter_to_num_column(QChar letter) {
    return letter.toUpper().unicode() - 65 + 1 ;
}

// scan int value on keyboard unless 0
int Tools::scanInt() {
    /*string tmp ;
    int res ;
    do {
        cin >> tmp;
        res = atoi(tmp.c_str()) ;
    }
    while (res==0) ;
    return res ;*/
    return 0 ;
}

