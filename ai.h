#include "board.h"
#include "validMoves.h"
#include <vector>
#include "piece.h"

#ifndef AIALGORITHM
#define AIALGORITHM

class AI
{
public:
    int calculateBestMove(Board board, ValidMoves *checkValidMoves, int depth);
    void copyArray(Piece *copyFrom[8][8], Piece *copyTo[8][8]);
    void rankBoard(Piece *board[8][8], int &rank, int color, bool negate = false);
};

#endif