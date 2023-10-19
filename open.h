#include "board.h"
#include "piece.h"
#include "validMoves.h"

#ifndef OPEN
#define OPEN

class Open
{
private:
    ValidMoves checkValidMoves;

public:
    bool randomOpening(Board *board, Piece *boardPtr[8][8], int randomNumber);
    bool royLopez(Board *board, Piece *boardPtr[8][8]);
};

#endif