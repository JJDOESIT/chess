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
    bool isMoveValid(Board *board, Piece *boardPtr[8][8], int currentMove, std::vector<std::vector<std::vector<int>>> openingMoves);
    bool randomOpening(Board *board, Piece *boardPtr[8][8], int randomNumber);
    bool royLopez(Board *board, Piece *boardPtr[8][8]);
};

#endif